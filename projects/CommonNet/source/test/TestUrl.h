
#include "http/Url.h"

void TestUrl()
{
    Url url1("http://www.baidu.com/wget.apx/?name=ydh#anchor");
    Url url11("http://www.baidu.com/wget.apx/#anchor");
    Url url2("http://www.baidu.com/wget.apx/?name=ydh#");
    Url url3("http://www.baidu.com/wget.apx/?name=ydh");
    Url url4("http://www.baidu.com/wget.apx/?");
    Url url5("http://www.baidu.com/wget.apx/");
    Url url6("http://ydh:123@www.baidu.com/wget.apx");
    Url url7("http://www.baidu.com:20/");
    Url url8("http://www.baidu.com:20");
    Url url81("http://www.baidu.com:");
    Url url82("http://www.baidu.com/");
    Url url9("http://");
    Url url10("http:/");
}
