
#include "SocketHttpClient.h"
#include "socket_common\SocketUtils.h"

#include "Url\DogUrl.h"

SocketHttpClient::SocketHttpClient()
{
}

SocketHttpClient::~SocketHttpClient()
{
}

bool SocketHttpClient::Get(const DogStringA& urlStr)
{
    DogUrl url;
    ParseUrl(urlStr, url);

    if (!url.IsValid())
    {
        return false;
    }

    // 获得ip
    std::vector<DogStringA> ips;
    SocketUtils::GetIpByHostName(url.m_host, ips);
    if (ips.size() == 0)
    {
        return false;
    }

    SocketTcpClient client(ips[0], url.m_port);

    if (!client.Connect())
    {
        return false;;
    }

    // 拼接
    DogStringA strHttpHead;
    strHttpHead.append("GET / HTTP/1.1\r\n");
    strHttpHead.append(url.m_scheme);
    strHttpHead.append("/1.1\r\n");
    strHttpHead.append("Accept: */*\r\n");
    strHttpHead.append("Accept-Language: cn\r\n");
    strHttpHead.append("User-Agent: Mozilla/4.0\r\n");
    strHttpHead.append("Host: ");
    strHttpHead.append(url.m_host);
    strHttpHead.append("\r\n");
    strHttpHead.append("Cache-Control: no-cache\r\n");
    strHttpHead.append("Connection: Keep-Alive\r\n");
    strHttpHead.append("\r\n\r\n");

    client.SendMsg(strHttpHead);
    std::string msg = "";
    client.RcvMsg([&msg](char* buff, unsigned int buffSize)
    {
        // 如果想手动结束的话，返回false 
        msg.append(buff, buffSize);
        return true;
    });

    return false;
}

bool SocketHttpClient::Post(const DogStringA& url)
{
    return false;
}

void SocketHttpClient::SetUploadPercentCallBack(const DogPercentCallBack& callback)
{
    m_upLoadPercentCallBack = callback;
}

void SocketHttpClient::SetDownloadPercentCallBack(const DogPercentCallBack& callback)
{
    m_downLoadPercentCallBack = callback;
}

void SocketHttpClient::SetUploadStream(const SPDogStream& stream)
{
    m_upLoadStream = stream;
}

void SocketHttpClient::SetDownloadStream(const SPDogStream& stream)
{
    m_downLoadLoadStream = stream;
}
