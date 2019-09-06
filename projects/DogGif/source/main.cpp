
#include "DogGif/DogGif.h"
#include "file_utils_reader.h"
using namespace DogGifNSP;

int main()
{
    FileReader reader(L"D:\\projects\\my\\MyLibrary\\projects\\DogGif\\test\\test.gif", NULL, 0);
    size_t fileSize = reader.GetFileSize();
    u8* pBuff = new u8[fileSize];
    reader.GetBuff((char*)pBuff, fileSize);
    DogGif gif;
    gif.Init(pBuff, fileSize);
    return 1;
}


