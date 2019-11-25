
#pragma once
#include "DogUrl.h"
#include "console/color_print.h"
#include <vector>

namespace utilstest
{
    inline void Test_DogUrl()
    {
        std::vector<std::string> urls;
        urls.push_back("http://www.baidu.com/wget.apx/dd/?name=ydh#anchor");
        urls.push_back("http:\\\\www.baidu.com\\wget.apx/dd/?name=ydh#anchor");
        urls.push_back("http://www.baidu.com/wget.apx/#anchor");
        urls.push_back("http://www.baidu.com/wget.apx/dd/?name=ydh#anchor");
        urls.push_back("http://www.baidu.com/wget.apx/dd/?name=ydh#anchor");
        urls.push_back("http://www.baidu.com/wget.apx/dd?name=ydh#");
        urls.push_back("http://www.baidu.com/wget.apx/dd?name=ydh");
        urls.push_back("http://www.baidu.com/wget.apx/dd/cc?");
        urls.push_back("http://www.baidu.com/wget.apx/");
        urls.push_back("http://ydh:123@w/wget.apx");
        urls.push_back("http:///wget.apx");
        urls.push_back("http://@/wget.apx");
        urls.push_back("http://:@/wget.apx");
        urls.push_back("http://:@:/wget.apx");
        urls.push_back("http://:/wget.apx");
        urls.push_back("http://www.baidu.com:20/");
        urls.push_back("http://www.baidu.com:20");
        urls.push_back("http://www.baidu.com:");
        urls.push_back("http://www.baidu.com/");
        urls.push_back("http://");
        urls.push_back("http:/");

        for (auto& it : urls)
        {
            ColorPrintf(Gray, "\r\n");
            ColorPrintf(Gray, it.c_str());
            ColorPrintf(Gray, "\r\n");
            DogUrl url(it);
            ColorPrintf(Green, url.GetFormateUrl().c_str());
            ColorPrintf(Green, "\r\n");
        }

        ::system("pause");
    }
}
