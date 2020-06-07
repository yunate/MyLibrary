
#include "../LogDogConfig.h"
#include "../LogDogDef.h"

#include "file/ini_file.h"

#include <tchar.h>
BEG_NSP_DDM
// 文件不存在状态下每10s会尝试加载
#define FAILURE_TIME_PASS 10000

// 文件存在状态每3min会尝试加载
#define CUCCESS_TIME_PASS 160000

LogDogConfig::LogDogConfig(const ddstr& path, const ddstr& name) :
    m_path(path),
    m_name(name)
{
    ReLoad();
}

void LogDogConfig::TryReload(bool atonce/* = false*/)
{
    bool needReload = false;

    if (!atonce)
    {
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
    }
    else
    {
        needReload = true;
    }

    if (needReload)
    {
        ReLoad();
    }
}

bool LogDogConfig::GetStrVal(const ddstr & key, ddstr& val)
{
    auto it = m_keyValue.find(key);

    if (it == m_keyValue.end())
    {
        return false;
    }

    val = it->second;
    return true;
}

bool LogDogConfig::GetBool(const ddstr & key)
{
    ddstr val;

    // 不存在认为是假
    if (!GetStrVal(key, val))
    {
        return false;
    }

    // '0' 认为是假
    if (val.length() == 1 && val[0] == _DDT('0'))
    {
        return false;
    }

    // "FALSE" 认为是假
    if (val.length() == 4 &&
        ::toupper(0) == _DDT('F') &&
        ::toupper(0) == _DDT('A') &&
        ::toupper(0) == _DDT('L') &&
        ::toupper(0) == _DDT('E'))
    {
        return false;
    }

    // 其他认为是true
    return true;
}

int LogDogConfig::GetInt32(const ddstr & key)
{
    ddstr val;

    // 不存在认为是假
    if (!GetStrVal(key, val))
    {
        return 0;
    }

    return ::_tstoi(val.c_str());
}

void LogDogConfig::ReLoad()
{
    m_keyValue.clear();
    m_timer.ReSet();
    m_errorCode = LogDogConfigErrorCode::LDC_NO_ERROR;
    sp_ini_file spIniFile(ini_file::create_obj(m_path));

    if (spIniFile == NULL)
    {
        m_errorCode = LogDogConfigErrorCode::LDC_NO_CONFIG_FILE;
        return;
    }

    std::vector<ddstr> names = spIniFile->get(NULL, NULL);
    bool hasName = false;

    for (size_t i = 0; i < names.size(); ++i)
    {
        if (names[i] == m_name)
        {
            hasName = true;
            break;
        }
    }

    if (!hasName)
    {
        m_errorCode = LogDogConfigErrorCode::LDC_NO_MATCH_NAME;
        return;
    }

    std::vector<ddstr> keys = spIniFile->get(m_name.c_str(), NULL);

    for (auto it : keys)
    {
        std::vector<ddstr> vals = spIniFile->get(m_name.c_str(), it.c_str());

        if (vals.size() == 1)
        {
            m_keyValue[it] = vals[0];
        }
    }
}

/* 分析配置文件是否有错误
@return 错误码 返回LDC_NO_ERROR表示成功
*/
LogDogConfigErrorCode LogDogConfig::GetErrorCode()
{
    return m_errorCode;
}

ddstr & LogDogConfig::GetConfigPath()
{
    return m_path;
}

ddstr & LogDogConfig::GetConfigName()
{
    return m_name;
}
END_NSP_DDM
