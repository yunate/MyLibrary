#pragma once
#include "DogUrl.h"

namespace utilstest
{
    inline void Test_DogUrl()
    {
        DogUrl url1("http://www.baidu.com/wget.apx/dd/?name=ydh#anchor");
        DogUrl url11("http://www.baidu.com/wget.apx/#anchor");
        DogUrl url2("http://www.baidu.com/wget.apx/dd?name=ydh#");
        DogUrl url3("http://www.baidu.com/wget.apx/dd?name=ydh");
        DogUrl url4("http://www.baidu.com/wget.apx/dd/cc?");
        DogUrl url5("http://www.baidu.com/wget.apx/");
        DogUrl url6("http://ydh:123@w/wget.apx");
        DogUrl url61("http:///wget.apx");
        DogUrl url62("http://@/wget.apx");
        DogUrl url63("http://:@/wget.apx");
        DogUrl url64("http://:@:/wget.apx");
        DogUrl url65("http://:/wget.apx");
        DogUrl url7("http://www.baidu.com:20/");
        DogUrl url8("http://www.baidu.com:20");
        DogUrl url81("http://www.baidu.com:");
        DogUrl url82("http://www.baidu.com/");
        DogUrl url9("http://");
        DogUrl url10("http:/");
    }
}
