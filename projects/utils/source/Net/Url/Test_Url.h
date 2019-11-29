
#pragma once
#include "DogUrl.h"
#include "console/color_print.h"
#include <vector>

namespace utilstest
{
    inline void Test_DogUrl()
    {
        std::vector<std::string> urls;
        urls.push_back("http://www.baidu.com:20/");
        urls.push_back("http://www.baidu.com:20/?#aa");
        urls.push_back("http:\\\\FF:123@www.baidu.com:80\\wget.apx\\/dd\\/?name=ydh#anchor");
        urls.push_back("http:\\\\:123@www.baidu.com:83\\wget.apx//dd/?name=ydh#anchor");
        urls.push_back("http:\\\\FF:@www.baidu.com:82\\wget.apx\\\\dd/?name=ydh#anchor");
        urls.push_back("http:\\\\FF@www.baidu.com:81\\wget.apx/dd\\\\?name=ydh#anchor");
        urls.push_back("http:\\\\FF@www.baidu.com:\\wget.apx/dd//?name=ydh#anchor");
        urls.push_back("http:\\\\FF@www.baidu.com\\wget.apx/dd/\\?name=ydh#anchor");
        urls.push_back("http:\\\\FF@\\wget.apx/dd/?name=ydh#anchor");
        urls.push_back("http://www.baidu.com/wget.apx/dd/?name=ydh#anchor");
        urls.push_back("http://www.baidu.com#anchor?name=ydh/wget.apx/dd/");
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
        urls.push_back("http:///?#");
        urls.push_back("http://w/?dada#");
        urls.push_back("http://w/?dada#daada");
        urls.push_back("http://w/#dada?daada");
        urls.push_back("http://w/#dada#ab");
        urls.push_back("http://");
        urls.push_back("http:/");

        for (auto& it : urls)
        {
            ColorPrintf(Gray, "\r\n");
            ColorPrintf(Gray, it.c_str());
            ColorPrintf(Gray, "\r\n");
            DogUrl url;
            ParseUrl(it, url);
            ColorPrintf(Green, "norml:");
            ColorPrintf(Green, url.GetFormatedUrl().c_str());

            DogUrl urlEx;
            ParseUrlRegex(it, urlEx);
            ColorPrintf(Green, "\r\nregex:");
            ColorPrintf(Green, urlEx.GetFormatedUrl().c_str());
            ColorPrintf(Green, "\r\n");
        }

        ::system("pause");
    }
}
