#ifndef AUTOBOTS_CLIENT_SVHOST_TOKEN_UTIL_H_
#define AUTOBOTS_CLIENT_SVHOST_TOKEN_UTIL_H_

#include "base/win/scoped_handle.h"
#include <vector>

bool IsSessionActive(DWORD session_id);
DWORD GetActiveSessionId();

HRESULT FindProcessesInSession(DWORD session_id,
                               const wchar_t* search_name,
                               std::vector<DWORD>* process_ids_found);

HRESULT GetPidsInSession(const wchar_t* exe_name,
                         DWORD session_id,
                         std::vector<DWORD>* pids);

HRESULT GetProcessPidsForActiveUserOrSession(const wchar_t* exe_name,
                                             std::vector<DWORD>* pids);

HRESULT GetExplorerPidForCurrentUserOrSession(DWORD* pid);

HRESULT GetImpersonationToken(DWORD process_id, base::win::ScopedHandle* token);                            

HRESULT GetLoggedOnUserToken(base::win::ScopedHandle* token);

HRESULT GetLinkedToken(base::win::ScopedHandle& token, base::win::ScopedHandle* linked_token);

#endif // AUTOBOTS_CLIENT_SVHOST_VISTA_UTIL_H_