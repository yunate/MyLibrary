
#include "../LogDogConfig.h"
#include "../LogDogDef.h"
#include "init_file/init_file.h"

// 文件不存在状态下每10s会尝试加载
#define FAILURE_TIME_PASS 10000

// 文件存在状态每3min会尝试加载
#define CUCCESS_TIME_PASS 160000

LogDogConfig::LogDogConfig(const DogString& path, const DogString& name)
{
    m_configEntry.m_path = path;
    m_configEntry.m_name = name;
    ReLoad();
}

void LogDogConfig::TryReload()
{
    bool needReload = false;

    if (m_errorCode == LogDogConfigErrorCode::LDC_NO_CONFIG_FILE)
    {
        // 文件不存在状态下每10s会尝试加载
        if (m_timer.GetTimePass() > FAILURE_TIME_PASS)
        {
            needReload = true;
        }
    }
    else
    {
        // 文件存在状态每3min会尝试加载
        if (m_timer.GetTimePass() > CUCCESS_TIME_PASS)
        {
            needReload = true;
        }
    }

    if (needReload)
    {
        ReLoad();
    }
}

void LogDogConfig::ReLoad()
{
    m_timer.ReSet();
    m_errorCode = LogDogConfigErrorCode::LDC_NO_ERROR;
    IniFile* iniFile = IniFile::CreateObj(m_configEntry.m_path);

    if (iniFile == NULL)
    {
        m_errorCode = LogDogConfigErrorCode::LDC_NO_CONFIG_FILE;
        return;
    }

    std::vector<DogString> names = iniFile->Get(NULL, NULL);
    bool hasName = false;

    for (size_t i = 0; i < names.size(); ++i)
    {
        if (names[i] == m_configEntry.m_name)
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

    std::vector<DogString> levels = iniFile->Get(m_configEntry.m_name.c_str(), _DogT("level"));

    if (levels.size() > 0 && levels[0].size() > 0)
    {
        int level = levels[0][0] - _DogT('0');

        if (level >= (int)LogDogConfigLevel::LDC_LEVEL_0 && level < (int)LogDogConfigLevel::LDC_LEVEL_END)
        {
            m_configEntry.m_level = (LogDogConfigLevel)level;
        }
    }

    std::vector<DogString> dump = iniFile->Get(m_configEntry.m_name.c_str(), _DogT("dump_to_file"));

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

    std::vector<DogString> upload = iniFile->Get(m_configEntry.m_name.c_str(), _DogT("upload"));

    if (upload.size() > 0 && upload[0].size() > 0)
    {
        if (upload[0] == _DogT("true") || upload[0][0] != _DogT('0'))
        {
            m_configEntry.m_isNeedUpload = true;
        }
        else
        {
            m_configEntry.m_isNeedUpload = false;
        }
    }

    delete iniFile;
    iniFile = NULL;
}

/* 分析配置文件是否有错误
@return 错误码 返回LDC_NO_ERROR表示成功
*/
LogDogConfigErrorCode LogDogConfig::GetErrorCode()
{
    return m_errorCode;
}

/** 获得日志配置
@return 日志配置
*/
LogDogConfigEntry& LogDogConfig::GetLogDogConfigEntry()
{
    return m_configEntry;
}

