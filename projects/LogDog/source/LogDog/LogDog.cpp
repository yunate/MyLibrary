#include "LogDog.h"

LogDog::LogDog()
{
}

LogDog::~LogDog()
{
}

bool LogDog::Init(const DogString& path, const DogString & name)
{
    // 加载配置文件，不要去判断是否加载成功，如果加载失败了，m_config只保存路径和名称，以便后续处理
    m_config.ReLoad(path, name);

    // 初始化任务队列
    m_taskque.reset(new(std::nothrow) SimpleTaskQueue());

    if (m_taskque == NULL)
    {
        return false;
    }

    if (!m_taskque->Start())
    {
        return false;
    }



    return true;
}
