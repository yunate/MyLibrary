#ifndef __FILE_UTILS_H_
#define __FILE_UTILS_H_

#include <string>
#include <functional>

/** 一行一行的读文件 , 每次读一个wchar
@param [in] path 路径
@param [in] checker 文件头校验
@param [in] checkSize checker的大小
@param [in] callback 回调
@return 是否成功
*/
bool ReadFileByLineW(const std::wstring& path, const unsigned char* checker, const size_t checkSize, std::function<bool(const std::wstring&line)> callback);

/** 一行一行的读文件 UCS-2 Little Endian 编码
@param [in] path 路径
@param [in] callback 回调
@return 是否成功
*/
bool ReadUCS2FileByLine(const std::wstring& path, std::function<bool(const std::wstring&line)> callback);

/** 一行一行的读文件 , 每次读一个char
@param [in] path 路径
@param [in] checker 文件头校验
@param [in] checkSize checker的大小
@param [in] callback 回调
@return 是否成功
*/
bool ReadFileByLine(const std::wstring& path, const unsigned char* checker, const size_t checkSize, std::function<bool(const std::string&line)> callback);

/** 一行一行的读文件 UTF8 编码
@param [in] path 路径
@param [in] callback 回调
@return 是否成功
*/
bool ReadUTF8FileByLine(const std::wstring& path, std::function<bool(const std::string&line)> callback);

/** 一行一行的读文件 UTF8-Bom 编码
@param [in] path 路径
@param [in] callback 回调
@return 是否成功
*/
bool ReadUTF8BomFileByLine(const std::wstring& path, std::function<bool(const std::string&line)> callback);

/** 写文件
@param [in] path 路径
@param [in] header 文件头校验
@param [in] headSize header的大小
@param [in] callback 回调函数 给调用者准备数据，准备好之后调用callback的callback
            WriteUCS2FileByBuff(L"D:\\test\\2.txt", [&buff](std::function<bool(void*, size_t)> callback){return true});
@return 是否成功
*/
bool WriteFileByBuff(const std::wstring& path, const unsigned char* header, const size_t headSize, std::function<bool(std::function<bool(void*, size_t)>)> callback);

/** 写文件 UCS-2 Little Endian 编码
@param [in] path 路径
@param [in] callback 回调函数 给调用者准备数据，准备好之后调用callback的callback
            WriteUCS2FileByBuff(L"D:\\test\\2.txt", [&buff](std::function<bool(void*, size_t)> callback){return true});
@return 是否成功
*/
bool WriteUCS2FileByBuff(const std::wstring& path, std::function<bool(std::function<bool(void*, size_t)>)> callback);

#endif //__FILE_UTILS_H_
