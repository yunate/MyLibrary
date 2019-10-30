
#ifndef __LOG_EXECUTOR_H_
#define __LOG_EXECUTOR_H_

#include "typedef/DogString.h"
#include "LogDogConfig.h"

/** 日志文件单个最大大小 5M
*/
const int g_file_size = 5242880;

class ILogExecutor
{
public:
    virtual ~ILogExecutor()
    {
    }

    /** 日志后续处理
    @param [in] logStr 日志字符串
    @param [in] config 日志配置
    @return 是否成功
    */
    virtual bool Executor(const DogString& logStr, const std::shared_ptr <LogDogConfig>& config) = 0;
};

/** 写到文件
*/
class DumpToFileExecutor :
    public ILogExecutor
{
public:
    /** 构造函数
    */
    DumpToFileExecutor();

    /** 日志后续处理
    @param [in] logStr 日志字符串
    @param [in] config 日志配置
    @return 是否成功
    */
    virtual bool Executor(const DogString& logStr, const std::shared_ptr <LogDogConfig>& config);

private:
    /** 获取日志文件路径，如果不存在则创建
    @param [in, out] logLen 日志长度
    @param [in] baseDirBath 目录路径
    @return 日志文件路径
    */
    DogString GetAndCreateLogFile(size_t logLen, const DogString& baseDirBath);

    /** 检查文件大小是否符合预期，如果不符合重新创建文件
    @param [in, out] logLen 日志长度
    @param [in, out] filePath 当前文件路径
    @return 是否成功
    */
    bool CheckFileSizeAndCreate(size_t logLen, DogString& filePath);

    /** 比如 "910",执行后变成 "911"
    @param [in, out] 数据
    @param [in] len 长度
    @return 是否成功；如果buff不是数字返回false,如果达到最大值，循环到0
    */
    bool StrInc(DogChar* buff, int len);
};

/** 传到网络
*/
class UpLoadExecutor :
    public ILogExecutor
{
public:
    /** 日志后续处理
    @param [in] logStr 日志字符串
    @param [in] config 日志配置
    @return 是否成功
    */
    virtual bool Executor(const DogString& logStr, const std::shared_ptr <LogDogConfig>& config);
};
#endif //__LOG_EXECUTOR_H_
