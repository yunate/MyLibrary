//
//#include "big_file_utils.h"
//
//#include <windows.h>
//
//bool HandleBigFileByLineW(const std::wstring & path, const unsigned char * checker, const size_t checkSize, std::function<bool(const std::wstring&line)> callback)
//{
//    bool success = false;
//
//    //存取模式
//    DWORD dAccessType = (GENERIC_READ);
//
//    //共享模式
//    DWORD dShareType = FILE_SHARE_READ;
//
//    // 打开文件句柄
//    HANDLE hFile = ::CreateFile(path.c_str()
//                              , dAccessType           // 访问模式
//                              , dShareType            // 共享模式
//                              , NULL
//                              , OPEN_EXISTING         // 如果存在则打开，否则失败
//                              , FILE_FLAG_OVERLAPPED  // 。。。
//                              , NULL);
//
//
//    if (hFile == INVALID_HANDLE_VALUE)
//    {
//        return false;
//    }
//
//    DWORD dFileSize = ::GetFileSize(hFile, NULL);
//
//    // 创建映射句柄
//    HANDLE hFileMap = ::CreateFileMapping(hFile,
//                                          NULL,
//                                          PAGE_READONLY,  // 注意，和createfile要一致
//                                          0,
//                                          dFileSize,
//                                          NULL);
//
//
//    if (hFileMap == NULL)
//    {
//        ::CloseHandle(hFile);
//        return false;
//    }
//
//    ::CloseHandle(hFile);
//
//    DWORD dFileBlock = 1024 * 1024 * 5;
//    DWORD dBegin = 0;
//    DWORD dLen = 0;
//
//    while (dBegin < dFileSize)
//    {
//        if (dBegin > dFileSize - dFileBlock)
//        {
//            dLen = dFileSize - dBegin;
//        }
//        else
//        {
//            dLen = dFileBlock;
//        }
//
//        LPVOID pFileBlock = ::MapViewOfFile(hFileMap,
//                                            FILE_MAP_READ,  // 注意，和createfile要一致
//                                            0,
//                                            dBegin,     // 开始位置
//                                            dLen);     // 映射长度
//
//        LPVOID pFileBlock1 = ::MapViewOfFile(hFileMap,
//                                            FILE_MAP_READ,  // 注意，和createfile要一致
//                                            0,
//                                            dBegin + dLen,     // 开始位置
//                                            dLen);     // 映射长度
//
//        if (pFileBlock == NULL)
//        {
//            break;
//        }
//
//        for (DWORD i = 0; i < dLen; ++i)
//        {
//        }
//
//        // “释放”掉虚拟内存
//        ::UnmapViewOfFile(pFileBlock);
//        dBegin += dLen;
//    }
//
//    ::CloseHandle(hFileMap);
//    return success;
//}
//
//bool HandleBigFileByLine(const std::wstring & path, const unsigned char * checker, const size_t checkSize, std::function<bool(const std::string&line)> callback)
//{
//    return false;
//}
