
#ifndef __LOG_EXECUTOR_H_
#define __LOG_EXECUTOR_H_

#include "base/g_def.h"
#include "LogDogConfig.h"
BEG_NSP_DDM
class ILogExecutor
{
public:
    virtual ~ILogExecutor()
    {
    }

    /** 日志后续处理
    @param [in] logStr 日志字符串
    @return 是否成功
    */
    virtual bool Executor(const ddstr& logStr) = 0;
};

/** 提供一个写到文件的处理器
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
    @return 是否成功
    */
    virtual bool Executor(const ddstr& logStr);

private:
    /** 获取日志文件路径，如果不存在则创建
    @param [in, out] logLen 日志长度
    @param [in] baseDirBath 目录路径
    @return 日志文件路径
    */
    ddstr GetAndCreateLogFile(size_t logLen, const ddstr& baseDirBath);

    /** 检查文件大小是否符合预期，如果不符合重新创建文件
    @param [in, out] logLen 日志长度
    @param [in, out] filePath 当前文件路径
    @return 是否成功
    */
    bool CheckFileSizeAndCreate(size_t logLen, ddstr& filePath);

    /** 比如 "910",执行后变成 "911"
    @param [in, out] 数据
    @param [in] len 长度
    @return 是否成功；如果buff不是数字返回false,如果达到最大值，循环到0
    */
    bool StrInc(ddchar* buff, int len);
};

/** 提供一个传到网络的处理器
*/
class UpLoadExecutor :
    public ILogExecutor
{
public:
    /** 日志后续处理
    @param [in] logStr 日志字符串
    @return 是否成功
    */
    virtual bool Executor(const ddstr& logStr);
};
END_NSP_DDM
#endif //__LOG_EXECUTOR_H_
