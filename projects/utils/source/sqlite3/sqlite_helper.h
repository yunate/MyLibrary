#ifndef __SQLITE3_H_
#define __SQLITE3_H_

#include <string>

#include "sqlite3.h"  

//#pragma comment(lib, "Sqlite3/lib/sqlite3.lib")

class SqlVec
{
public:
    SqlVec()
        : m_ppValue(0)
        , m_nCol(0)
        , m_nRaw(0)
    {

    }

    ~SqlVec()
    {

    }

public:
    int GetRaw()
    {
        return m_nRaw;
    }

    int GetCol()
    {
        return m_nCol;
    }

    char * GetAt(int x, int y)
    {
        return m_ppValue[x * m_nCol + y];
    }

public:
    void Init(char ** ppValue, int nRaw, int nCol)
    {
        m_ppValue = ppValue;
        m_nRaw = nRaw;
        m_nCol = nCol;
    }

private:
    char ** m_ppValue;
    int        m_nRaw;
    int        m_nCol;
};

class SQLiteHelper
{
public:
    SQLiteHelper(std::string sPath);
    virtual ~SQLiteHelper();

public:
    bool    ExecSQL(const char *sql);
    bool    RawQuery(const char *sql, SqlVec & vec);
    bool    OpenDB(const char *path);
    bool    CloseDB();

    inline char *    GetErrorMsg()
    {
        return m_pErrorMessge;
    }

private:
    sqlite3 *    m_pDB;
    char *        m_pErrorMessge;
};

#endif

