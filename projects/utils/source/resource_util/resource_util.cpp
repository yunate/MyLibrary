#include "resource_uti.h"
#include <windows.h>

namespace resourceutil
{
    bool WriteToFile(HANDLE hFile, LPBYTE lpBuffer, DWORD dwTotal)
    {
        DWORD dwRemain = dwTotal;
        LPBYTE lpPos = lpBuffer;
        do
        {
            DWORD dwWritten = 0;
            if (!::WriteFile(hFile, lpPos, dwRemain, &dwWritten, NULL))
            {
                return false;
            }
            dwRemain -= dwWritten;
            lpPos += dwWritten;
        } while (dwRemain);

        return true;
    }

    bool ReleaseResource(HMODULE hModule, unsigned int resourceId, const std::wstring& resourceType, const std::wstring& target)
    {
        HRSRC hrc = ::FindResource(hModule, MAKEINTRESOURCE(resourceId), resourceType.c_str());
        if (hrc == NULL)
        {
            return false;
        }

        HGLOBAL hGlobal = ::LoadResource(hModule, hrc);
        if (hGlobal == NULL)
        {
            return false;
        }

        DWORD dwSize = ::SizeofResource(hModule, hrc);
        LPVOID pData = ::LockResource(hGlobal);

        HANDLE hFile = ::CreateFile(
            target.c_str(),
            GENERIC_WRITE,
            0,
            0,
            CREATE_ALWAYS,
            0,
            0);

        if (hFile == INVALID_HANDLE_VALUE)
        {
            return false;
        }

        bool bRet = WriteToFile(hFile, (LPBYTE)pData, dwSize);
        ::CloseHandle(hFile);

        return bRet;
    }
}
