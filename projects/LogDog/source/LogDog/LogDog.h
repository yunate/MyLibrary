
#ifndef __LOGDOG_H_
#define __LOGDOG_H_

#include "LogDogConfig.h"

#include "task/SimpleTaskQueue.h"
#include "typedef/DogString.h"

#include <memory>

class LogDog :
    public NonCopyable
{
public:
    /** 构造函数
    */
    LogDog();

    /** 析构函数
    */
    ~LogDog();

    /** 初始化
    @param [in] path 配置文件路径
    @param [in] name 该日志的名称
    */
    bool Init(const DogString& path, const DogString& name);

private:
    /** 配置文件
    */
    LogDogConfig m_config;

    /** 任务队列
    */
    std::shared_ptr<SimpleTaskQueue> m_taskque;
};


#endif //__NAME_H_
