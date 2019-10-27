
#include "Export/ILogDog.h"
#include "init_file/init_file.h"

/** 日志的配置文件
*/
class LogDogConfigImpl :
    public ILogDogConfig
{
public:
    /** 构造函数，并初始化
    @param [in] path 配置文件路径
    @param [in] name 在配置中查找的日志名称
    */
    LogDogConfigImpl(const std::wstring& path, const std::wstring& name)
    {
        ReLoad(path, name);
    }

public:
    /** 初始化
    @param [in] path 配置文件路径
    */
    virtual void ReLoad(const std::wstring& path, const std::wstring& name)
    {
        m_errorCode = LogDogConfigErrorCode::LDC_NO_ERROR;
        m_configEntry.m_path = path;
        m_configEntry.m_name = name;
        IniFile* iniFile = IniFile::CreateObj(path, true);

        if (iniFile == NULL)
        {
            m_errorCode = LogDogConfigErrorCode::LDC_NO_CONFIG_FILE;
            return;
        }

        std::vector<DogString> names = iniFile->Get(NULL, NULL);
        bool hasName = false;

        for (size_t i = 0; i < names.size(); ++i)
        {
            if (names[i] == name)
            {
                hasName = true;
                break;
            }
        }

        if (!hasName)
        {
            m_errorCode = LogDogConfigErrorCode::LDC_NO_MATCH_NAME;
            delete iniFile;
            iniFile = NULL;
            return;
        }

        std::vector<DogString> levels = iniFile->Get(name.c_str(), _DogT("level"));

        if (levels.size() > 0 && levels[0].size() > 0)
        {
            int level = levels[0][0] - _DogT('0');

            if (level >= (int)LogDogConfigLevel::LDC_LEVEL_0 && level < (int)LogDogConfigLevel::LDC_LEVEL_END)
            {
                m_configEntry.m_level = (LogDogConfigLevel)level;
            }
        }

        std::vector<DogString> dump = iniFile->Get(name.c_str(), _DogT("dump_to_file"));

        if (dump.size() > 0 && dump[0].size() > 0)
        {
            if (dump[0] == _DogT("true") || dump[0][0] != _DogT('0'))
            {
                m_configEntry.m_isNeedDmpToFile = true;
            }
            else
            {
                m_configEntry.m_isNeedDmpToFile = false;
            }
        }

        delete iniFile;
        iniFile = NULL;
    }

    /* 分析配置文件是否有错误
    @return 错误码 返回LDC_NO_ERROR表示成功
    */
    virtual LogDogConfigErrorCode GetErrorCode()
    {
        return m_errorCode;
    }

    /** 获得日志配置
    @return 日志配置
    */
    virtual LogDogConfigEntry& GetLogDogConfigEntry()
    {
        return m_configEntry;
    }

private:
    /** 错误码
    */
    LogDogConfigErrorCode m_errorCode = LogDogConfigErrorCode::LDC_NO_ERROR;

    /** 当前数据条目
    */
    LogDogConfigEntry m_configEntry;
};

std::shared_ptr<ILogDogConfig> ILogDogConfig::Create(const std::wstring& path, const std::wstring& name)
{
    return std::shared_ptr<ILogDogConfig>(new(std::nothrow) LogDogConfigImpl(path, name));
}
