#include "sqlite_helper.h"  

SQLiteHelper::SQLiteHelper(std::string sPath)
    : m_pDB(0)
    , m_pErrorMessge(0)
{

    FILE * pFile = 0;
    fopen_s(&pFile, sPath.c_str(), "r");

    if (!pFile)
    {
        fopen_s(&pFile, sPath.c_str(), "a");
    }

    if (!pFile)
    {
        // 文件创建失败
        m_pErrorMessge = "cannot find and create db file failure";
        return;
    }

    fclose(pFile);

    if (!OpenDB(sPath.c_str()))
    {
        m_pErrorMessge = "open db failure";
    }
}

SQLiteHelper::~SQLiteHelper()
{
    CloseDB();
}

int callback(void*para, int nCount, char** pValue, char** pName)
{
    para;
    nCount;
    pValue;
    pName;
    std:: string s = "";

//     for (int i=0; i < nCount; i++)
//     {
//         s+=pValue[i];
//     }

    return 0;
}


bool SQLiteHelper::ExecSQL(const char *sql)
{
    return SQLITE_OK == sqlite3_exec(m_pDB, sql, callback, 0, &m_pErrorMessge);
}

bool SQLiteHelper::RawQuery(const char *sql, SqlVec & vec)
{
    int nRaw, nCol;
    char **result;

    if (SQLITE_OK == sqlite3_get_table(m_pDB, sql, &result, &nRaw, &nCol, &m_pErrorMessge))
    {
        vec.Init(result, nRaw, nCol);
        return true;
    }

    return false;
}

bool SQLiteHelper::OpenDB(const char *path)
{
    return SQLITE_OK == sqlite3_open(path, &m_pDB);
}

bool SQLiteHelper::CloseDB()
{
    return SQLITE_OK == sqlite3_close(m_pDB);
}