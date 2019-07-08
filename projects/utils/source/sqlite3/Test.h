#pragma once
#include "sqlite_helper.h"

namespace utilstest
{
    inline void Test_Sql0()
    {
        SQLiteHelper * help = new SQLiteHelper("C:\\Users\\ydh\\Desktop\\aa\\SqlTest0");

        if (0 != help->GetErrorMsg())
        {
            delete help;
            return;
        }

        std::string sDropTable = "drop table mytable";
        help->ExecSQL(sDropTable.c_str());

        std::string temp;
        temp = "CREATE TABLE mytable (NAME TEXT NOT NULL, AGE INT NOT NULL);";
        help->ExecSQL(temp.c_str());

        temp = "insert into mytable values('µÈ´ý', 25)";
        help->ExecSQL(temp.c_str());
        temp = "select * from mytable";
        SqlVec vec;
        help->RawQuery(temp.c_str(), vec);
        delete help;
    }
}
