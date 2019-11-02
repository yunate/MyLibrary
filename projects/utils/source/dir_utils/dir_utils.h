#ifndef _FILE_AND_DIR_UTIL_H__
#define _FILE_AND_DIR_UTIL_H__

#include "typedef/DogString.h"

#include <string>

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
}

#endif // _FILE_AND_DIR_UTIL_H__