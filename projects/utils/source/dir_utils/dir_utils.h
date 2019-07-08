#ifndef _FILE_AND_DIR_UTIL_H__
#define _FILE_AND_DIR_UTIL_H__

#include <string>

namespace dir_uitls
{
    /** 是否是文件夹
    @param [in] path 路径
    */
    bool IsDir(const std::wstring& path);

    /** 判断文件是否存在
    @param [in] filePath 文件路径
    */
    bool IsFileExist(const std::wstring& filePath);

    /** 判断文件夹是否存在
    @param [in] dirPath 文件夹路径
    */
    bool IsDirExist(const std::wstring& dirPath);

    /** 判断文件或文件夹是否存在
    @param [in] path 路径
    */
    bool IsPathExist(const std::wstring& path);

    /** 创建文件
    @param [in] filePath 文件路径
    */
    bool CreateFile_(const std::wstring& filePath);

    /** 删除文件夹
    @param [in] dfilePath 文件路径
    */
    bool DeleteFile_(const std::wstring& dfilePath);

    /** 删除文件夹
    @param [in] dirPath 文件夹路径
    */
    bool DeleteDir(const std::wstring& dirPath);

    /** 创建文件夹
    @param [in] dirPath 文件夹路径
    */
    bool CreateDir(const std::wstring& dirPath);
}

#endif // _FILE_AND_DIR_UTIL_H__