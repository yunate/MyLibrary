
#ifndef __BIG_FILE_UTILS_H_
#define __BIG_FILE_UTILS_H_

#include <string>
#include <functional>

/** 一行一行的读文件 , 每次读一个wchar
@param [in] path 路径
@param [in] checker 文件头校验
@param [in] checkSize checker的大小
@param [in] callback 回调
@return 是否成功
*/
bool HandleBigFileByLineW(const std::wstring& path, const unsigned char* checker, const size_t checkSize, std::function<bool(const std::wstring&line)> callback);


/** 一行一行的读文件 , 每次读一个char
@param [in] path 路径
@param [in] checker 文件头校验
@param [in] checkSize checker的大小
@param [in] callback 回调
@return 是否成功
*/
bool HandleBigFileByLine(const std::wstring& path, const unsigned char* checker, const size_t checkSize, std::function<bool(const std::string&line)> callback);


#endif //__BIG_FILE_UTILS_H_
