
#include "MemoryStream.h"
#include "FileStream.h"

namespace utilstest
{
    void Test_MemoryStream()
    {
        MemoryStream * pDogStream = new MemoryStream(100);
        s8 buff[128] = {'a'};
        buff[127] = 0;
        pDogStream->Write((u8*)buff, 128);

        MemoryStream stream1 = (*pDogStream);
        stream1.Seek(1, 0);
        stream1.Write((u8*)buff, 127);
        stream1.ReSize(200);
        stream1.ReSize(1025);
        stream1.ReSize(0x40000000);

        delete pDogStream;
    }

    void Test_FileStream()
    {
        IDogStream * pDogStream = new FileStream("C:\\Users\\yudh\\Desktop\\test1\\filestream.txt");
        char buff[] = "hello file stream";
        pDogStream->Write((u8*)buff, sizeof(buff));
        pDogStream->Write((u8*)buff, sizeof(buff));
        s64 size = pDogStream->Size();
        char buff1[500] = {0};
        pDogStream->ReadAllA((u8*)buff1);
        delete pDogStream;
    }
}

