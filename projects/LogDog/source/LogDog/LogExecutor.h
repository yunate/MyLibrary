
#ifndef __LOG_EXECUTOR_H_
#define __LOG_EXECUTOR_H_

#include "typedef/DogString.h"

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
    virtual bool Executor(const DogString& logStr) = 0;
};

/** 写到文件
*/
class DumpToFileExecutor :
    public ILogExecutor
{
public:
    DumpToFileExecutor(const DogString& path);

    /** 日志后续处理
    @param [in] logStr 日志字符串
    @return 是否成功
    */
    virtual bool Executor(const DogString& logStr);

private:
    /** 目标文件夹路径
    */
    DogString m_path;
};

/** 传到网络
*/
class UpLoadExecutor :
    public ILogExecutor
{
public:
    /** 日志后续处理
    @param [in] logStr 日志字符串
    @return 是否成功
    */
    virtual bool Executor(const DogString& logStr);
};
#endif //__LOG_EXECUTOR_H_
