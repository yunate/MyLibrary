#include "LogDogConfig.h"
#include "init_file/init_file.h"

LogDogConfig::LogDogConfig()
{
}

LogDogConfig::LogDogConfig(const std::wstring& path, const std::wstring& name)
{
    ReLoad(path, name);
}

void LogDogConfig::ReLoad(const std::wstring& path, const std::wstring& name)
{
    m_errorCode = LogDogConfigErrorCode::LDC_NO_ERROR;
    m_configEntry.m_path = path;
    m_configEntry.m_name = name;
    IniFile * iniFile = IniFile::CreateObj(path, true);

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

