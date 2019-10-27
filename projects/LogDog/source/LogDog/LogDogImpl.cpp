
#include "Export/ILogDog.h"
#include "task/SimpleTaskQueue.h"
#include "typedef/DogString.h"

#include <map>

class LogDogImpl :
    public ILogDog
{
public:
    /** 构造函数
    @param [in] path 配置文件路径
    @param [in] name 该日志的名称
    */
    LogDogImpl(const DogString& path, const DogString& name)
    {
        // 加载配置文件，不要去判断是否加载成功，如果加载失败了，m_config只保存路径和名称，以便后续处理
        m_spConfig = ILogDogConfig::Create(path, name);

        if (m_spConfig == NULL)
        {
            return;
        }

        // 初始化任务队列
        m_spLogQue.reset(new(std::nothrow) SimpleTaskQueue());

        if (m_spLogQue == NULL)
        {
            return;
        }

        if (!m_spLogQue->Start())
        {
            return;
        }

        return;
    }

    /** 析构函数
    */
    ~LogDogImpl()
    {
    }

    /** 压入日志
    @param [in] log 日志实体
    */
    virtual void Push(std::shared_ptr<ILog>& log)
    {
        if (log == NULL)
        {
            return;
        }

        log->SetLogConfig(m_spConfig);
        m_spLogQue->PushTask(log);
    }

private:
    /** 配置文件
    */
    std::shared_ptr <ILogDogConfig> m_spConfig;

    /** 日志任务队列
    */
    std::shared_ptr<SimpleTaskQueue> m_spLogQue;
};

std::shared_ptr<ILogDog> ILogDog::Create(const DogString& path, const DogString& name)
{
    return std::shared_ptr<ILogDog>(new(std::nothrow) LogDogImpl(path, name));
}
