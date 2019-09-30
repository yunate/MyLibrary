
#include "MemoryStream.h"

namespace utilstest
{
    void Test_MemoryStream()
    {
        IDogStream * pDogStream = new MemoryStream(100);
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
}

