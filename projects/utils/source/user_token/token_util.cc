#include "token_util.h"

#include <Psapi.h>
#include <Shlwapi.h>
#include <wtsapi32.h>
#include <vector>

#include <base/win/scoped_handle.h>

const wchar_t* const kExplorer = L"EXPLORER.EXE";
const int kMaxProcesses = 1024;
const DWORD kInvalidSessionId = 0xFFFFFFFF;

HRESULT HRESULTFromLastError() {
  DWORD error_code = ::GetLastError();
  HRESULT hr = error_code != NO_ERROR ? HRESULT_FROM_WIN32(error_code) : E_FAIL;
  return hr;
}

HRESULT FindProcessesInSession(DWORD session_id,
                               const wchar_t* search_name,
                               std::vector<DWORD>* process_ids_found) {
  DWORD process_ids[kMaxProcesses] = {0};
  DWORD bytes_returned = 0;
  if (!::EnumProcesses(reinterpret_cast<DWORD*>(process_ids),
                       sizeof(process_ids),
                       reinterpret_cast<DWORD*>(&bytes_returned))) {
    HRESULT hr = HRESULTFromLastError();
    return hr;
  }

  int num_processes = bytes_returned / sizeof(process_ids[0]);
  for (int i = 0; i < num_processes; ++i) {
    HRESULT hr = 0;
    DWORD process_session = 0;
    if (!::ProcessIdToSessionId(process_ids[i], &process_session)) {
      hr = HRESULTFromLastError();
      continue;
    }

    if (process_session == session_id) {
      wchar_t module_name[MAX_PATH];
      base::win::ScopedHandle process_handle(::OpenProcess(
          PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, process_ids[i]));
      if (!::GetModuleFileNameEx(process_handle.Get(), NULL, module_name,
                                 arraysize(module_name))) {
        continue;
      }

      LPCWSTR module_file_name = ::PathFindFileName(module_name);
      if (!module_file_name) {
        continue;
      }
      if (!lstrcmpiW(module_file_name, search_name)) {
        process_ids_found->push_back(process_ids[i]);
      }
    }
  }

  return S_OK;
}

HRESULT GetPidsInSession(const wchar_t* exe_name,
                         DWORD session_id,
                         std::vector<DWORD>* pids) {
  pids->clear();

  HRESULT hr = FindProcessesInSession(session_id, exe_name, pids);
  if (FAILED(hr)) {
    return hr;
  }
  return pids->empty() ? HRESULT_FROM_WIN32(ERROR_NOT_FOUND) : S_OK;
}

bool IsSessionActive(DWORD session_id) {
  if (kInvalidSessionId == session_id) {
    return false;
  }

  WTS_CONNECTSTATE_CLASS wts_connect_state = WTSDisconnected;
  WTS_CONNECTSTATE_CLASS* ptr_wts_connect_state = NULL;
  DWORD bytes_returned = 0;
  if (::WTSQuerySessionInformation(
          WTS_CURRENT_SERVER_HANDLE, session_id, WTSConnectState,
          reinterpret_cast<LPTSTR*>(&ptr_wts_connect_state), &bytes_returned)) {
    wts_connect_state = *ptr_wts_connect_state;
    ::WTSFreeMemory(ptr_wts_connect_state);
    return WTSActive == wts_connect_state;
  }
  return false;
}

// Get the best guess as to the currently active session, or kInvalidSessionId
// if there is no active session.
DWORD GetActiveSessionId() {
  // WTSGetActiveConsoleSessionId retrieves the Terminal Services session
  // currently attached to the physical console.
  DWORD active_session_id = WTSGetActiveConsoleSessionId();
  if (IsSessionActive(active_session_id)) {
    return active_session_id;
  }

  // WTSGetActiveConsoleSessionId works for FUS, but it does not work for TS
  // servers where the current active session is always the console. We then use
  // a different method as below. We get all the sessions that are present on
  // the system, to see if we can find an active session.
  active_session_id = kInvalidSessionId;
  WTS_SESSION_INFO* session_info = NULL;
  DWORD num_sessions = 0;
  if (::WTSEnumerateSessions(WTS_CURRENT_SERVER_HANDLE, 0, 1, &session_info,
                             &num_sessions)) {
    // Pick the first active session we can find
    for (DWORD i = 0; i < num_sessions; ++i) {
      if (session_info[i].State == WTSActive) {
        // There is a user logged on to the WinStation associated with the
        // session.
        active_session_id = session_info[i].SessionId;
        break;
      }
    }

    ::WTSFreeMemory(session_info);
    return active_session_id;
  }
  return kInvalidSessionId;
}

HRESULT GetProcessPidsForActiveUserOrSession(const wchar_t* exe_name,
                                             std::vector<DWORD>* pids) {
  return GetPidsInSession(exe_name, GetActiveSessionId(), pids);
}

HRESULT GetExplorerPidForCurrentUserOrSession(DWORD* pid) {
  std::vector<DWORD> pids;
  HRESULT hr = GetProcessPidsForActiveUserOrSession(kExplorer, &pids);
  if (FAILED(hr)) {
    return hr;
  }
  *pid = pids[0];  // Return only the first instance of explorer.exe.
  return S_OK;
}

// Creates an impersonation token for the user running process_id.
// The caller is responsible for closing the returned handle.
HRESULT GetImpersonationToken(DWORD process_id,
                              base::win::ScopedHandle* token) {
  // Get a handle to the process.
  base::win::ScopedHandle process(::OpenProcess(
      PROCESS_DUP_HANDLE | PROCESS_QUERY_INFORMATION, TRUE, process_id));
  if (!process.IsValid()) {
    HRESULT hr(HRESULTFromLastError());
    return hr;
  }

  HRESULT result = S_OK;

  HANDLE process_token;
  if (!::OpenProcessToken(process.Get(), TOKEN_DUPLICATE | TOKEN_QUERY,
                          &process_token)) {
    result = HRESULTFromLastError();
  } else {
    HANDLE user_token;
    if (!::DuplicateTokenEx(process_token,
                            TOKEN_IMPERSONATE | TOKEN_QUERY |
                                TOKEN_ASSIGN_PRIMARY | TOKEN_DUPLICATE,
                            NULL, SecurityImpersonation, TokenPrimary,
                            &user_token)) {
      result = HRESULTFromLastError();
    }
    token->Set(user_token);
    CloseHandle(process_token);
  }
  return result;
}

HRESULT GetLoggedOnUserToken(base::win::ScopedHandle* token) {
  DWORD pid = 0;
  HRESULT hr = GetExplorerPidForCurrentUserOrSession(&pid);
  if (FAILED(hr)) {
    return hr;
  }
  hr = GetImpersonationToken(pid, token);
  if (FAILED(hr)) {
    return hr;
  }

  return S_OK;
}

HRESULT GetLinkedToken(base::win::ScopedHandle& token,
                       base::win::ScopedHandle* linked_token) {
  TOKEN_ELEVATION_TYPE ElevationType;
  DWORD dwRequiredLength = 0;
  if (!::GetTokenInformation(token.Get(), TokenElevationType, &ElevationType,
                             sizeof(TOKEN_ELEVATION_TYPE), &dwRequiredLength)) {
    return HRESULTFromLastError();
  }

  HRESULT result = S_OK;

  HANDLE hLinkedToken = NULL;
  TOKEN_LINKED_TOKEN LinkedToken = {0};
  switch (ElevationType) {
    case TokenElevationTypeLimited:
      if (!::GetTokenInformation(
              token.Get(), TokenLinkedToken, (VOID*)&LinkedToken,
              sizeof(TOKEN_LINKED_TOKEN), &dwRequiredLength)) {
        hLinkedToken = NULL;
        result = HRESULTFromLastError();
      }
      hLinkedToken = LinkedToken.LinkedToken;
      linked_token->Set(hLinkedToken);
      break;
    case TokenElevationTypeDefault:
    case TokenElevationTypeFull:
    default:
      hLinkedToken = NULL;
      result = ERROR_NO_TOKEN;
  }

  return result;
}