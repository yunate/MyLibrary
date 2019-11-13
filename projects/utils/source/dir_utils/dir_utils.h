#ifndef _FILE_AND_DIR_UTIL_H__
#define _FILE_AND_DIR_UTIL_H__

#include "typedef/DogString.h"

#include <string>
#include <vector>
#include <functional>

namespace dir_uitls
{
    /** 是否是文件夹
    @param [in] path 路径
    */
    bool IsDir(const DogString& path);

    /** 判断文件是否存在
    @param [in] filePath 文件路径
    */
    bool IsFileExist(const DogString& filePath);

    /** 判断文件夹是否存在
    @param [in] dirPath 文件夹路径
    */
    bool IsDirExist(const DogString& dirPath);

    /** 判断文件或文件夹是否存在
    @param [in] path 路径
    */
    bool IsPathExist(const DogString& path);

    /** 创建文件
    @param [in] filePath 文件路径
    */
    bool CreateFile_(const DogString& filePath);

    /** 删除文件夹
    @param [in] dfilePath 文件路径
    */
    bool DeleteFile_(const DogString& dfilePath);

    /** 删除文件夹
    @param [in] dirPath 文件夹路径
    */
    bool DeleteDir(const DogString& dirPath);

    /** 创建文件夹
    @param [in] dirPath 文件夹路径
    */
    bool CreateDir(const DogString& dirPath);

    /** 创建文件夹(嵌套创建)
    @param [in] dirPath 文件夹路径
    */
    bool CreateDirEx(const DogString& dirPath);

    /** 枚举目录 广度优先
    @param [in] dirPath 目录路径
    @param [in] callBack 回调函数，对每一个路径进行处理
                @param [in] path 路径
                @param [in] isDir 是否是目录
    */
    void EnumDir(const DogString& dirPath, std::function<void(const DogString& path, bool isDir)> callBack);

    /** 枚举目录 广度优先
    @param [in] dirPath 目录路径
    @param [in] out 输出路径vector
    @param [in] filter 对每一path进行过滤，返回true这放到out结果中，否则丢掉。filter为空时候当作返回true
                @param [in] path 路径
                @param [in] isDir 是否是目录
                @return true 将path放到out结果，false 丢掉
    */
    void EnumDir(const DogString& dirPath, std::vector<DogString>& out, std::function<bool(const DogString& path, bool isDir)> filter);
}

#endif // _FILE_AND_DIR_UTIL_H__