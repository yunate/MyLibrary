#ifndef __FILE_UTILS_H_
#define __FILE_UTILS_H_

#include <functional>

/** 一行一行的读文件 , 每次读一个wchar
@param [in] path 路径
@param [in] checker 文件头校验
@param [in] checkSize checker的大小
@param [in] callback 回调
@return 是否成功
*/
bool HandleFileByLineW(const std::wstring& path, const unsigned char* checker, const size_t checkSize, std::function<bool(const std::wstring&line)> callback);

/** 一行一行的读文件 UCS-2 Little Endian 编码
@param [in] path 路径
@param [in] callback 回调
@return 是否成功
*/
bool HandleUCS2FileByLine(const std::wstring& path, std::function<bool(const std::wstring&line)> callback);

/** 写文件
@param [in] path 路径
@param [in] header 文件头校验
@param [in] headSize header的大小
@param [in] callback 回调函数 返回即将要写入文件的内容，size 即将要写入文件的大小，请注意单双字节，双字节别忘了乘2,hasNext标识是否有下一条
@return 是否成功
*/
bool WriteFileByBuff(const std::wstring& path, const unsigned char* header, const size_t headSize, std::function<const void* (size_t& size, bool& hasNext)> callback);

/** 写文件 UCS-2 Little Endian 编码
@param [in] path 路径
@param [in] callback 回调函数 返回即将要写入文件的内容， size 即将要写入文件的大小，请注意单双字节，双字节别忘了乘2,hasNext标识是否有下一条
@return 是否成功
*/
bool WriteUCS2FileByBuff(const std::wstring& path, std::function<const void* (size_t& size, bool& hasNext)> callback);

#endif //__FILE_UTILS_H_
