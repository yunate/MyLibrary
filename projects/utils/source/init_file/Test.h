#pragma once
#include "init_file.h"

namespace utilstest
{
    inline void Test_Initfile0()
    {
        IniFile * pInitFIle = IniFile::CreateObj("C:\\Users\\ydh\\Desktop\\aa\\1.ini", true);

        if (!pInitFIle)
        {
            return;
        }

        pInitFIle->AddKey("Sec1", "key1", "1");
        pInitFIle->AddKey("Sec1", "key2", "1");
        pInitFIle->AddKey("Sec1", "key3", "1");
        pInitFIle->AddKey("Sec1", "key4", "1");

        pInitFIle->AddKey("Sec2", "key1", "1");
        pInitFIle->AddKey("Sec2", "key2", "1");
        pInitFIle->AddKey("Sec2", "key3", "1");
        pInitFIle->AddKey("Sec2", "key4", "1");

        pInitFIle->DelKey("Sec1", "key1");
        pInitFIle->DelSection("sec2");
        pInitFIle->ChangKey("sec1", "key2", "2");

        std::string ss = pInitFIle->GetKey("sec1", "key2");

        delete pInitFIle;
    }
}
