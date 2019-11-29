
#include "SocketHttpClient.h"
#include "socket_common/SocketUtils.h"

#include "timer_recorder/timer_recorder.h"
#include "Url/DogUrl.h"

/** 数据超时时间 (ms)
*/
static int DATA_TIME_OUT = 15000;

SocketHttpClient::SocketHttpClient():
    m_gTimeOut(0),
    m_dataTimeOut(DATA_TIME_OUT)
{
}

SocketHttpClient::~SocketHttpClient()
{
}

bool SocketHttpClient::Get(const DogStringA& urlStr)
{
    return MakeRequest(urlStr, "GET");
}

bool SocketHttpClient::Post(const DogStringA& url)
{
    return false;
}

bool SocketHttpClient::MakeRequest(const DogStringA& urlStr, const DogStringA& method)
{
    TimerRecorder gTimer;
    DogUrl url;
    ParseUrl(urlStr, url);

    if (!url.IsValid())
    {
        return false;
    }

    // 必须是http协议
    if (!(url.m_scheme.length() >= 4) &&
        (url.m_scheme[0] == 'h' || url.m_scheme[0] == 'H') &&
        (url.m_scheme[1] == 't' || url.m_scheme[1] == 'T') &&
        (url.m_scheme[2] == 't' || url.m_scheme[2] == 'T') &&
        (url.m_scheme[3] == 'p' || url.m_scheme[3] == 'P'))
    {
        return false;
    }

    DogCharA s = url.m_scheme[url.m_scheme.length() - 1];
    bool isSafe = (s == 's' || s == 'S');

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
        return false;
    }

    int iMode = 1;
    if (SOCKET_ERROR == ::ioctlsocket(client.GetSocketBean().GetSocket(), FIONBIO, (u_long FAR*)&iMode))
    {
        return false;
    }

    // 拼接
    DogStringA strHttpHead = method;
    strHttpHead.append(" ");
    strHttpHead.append(url.m_path);

    if (url.m_query.length() > 0)
    {
        strHttpHead.append("?");
        strHttpHead.append(url.m_query);
    }

    if (url.m_fragment.length() > 0)
    {
        strHttpHead.append("#");
        strHttpHead.append(url.m_fragment);
    }

    strHttpHead.append(" ");
    DogStringA upperScheme = url.m_scheme;
    std::transform(upperScheme.begin(), upperScheme.end(), upperScheme.begin(), ::toupper);
    strHttpHead.append(upperScheme);
    strHttpHead.append("/1.1\r\n");

    //strHttpHead.append("Accept: */*\r\n");
    //strHttpHead.append("Accept-Language: cn\r\n");
    //strHttpHead.append("User-Agent: Mozilla/4.0\r\n");
    strHttpHead.append("Host: ");
    strHttpHead.append(url.m_host);
    strHttpHead.append("\r\n");
    strHttpHead.append("Connection: close\r\n");
    strHttpHead.append("Keep-Alive: timeout=5,max=500\r\n");
    strHttpHead.append("\r\n\r\n");
    
    if (client.SendMsg(strHttpHead) != strHttpHead.length())
    {
        return false;
    }

    std::string msg = "";
    unsigned int buffSize = client.GetBuffSize();
    u8* pBuff = new (std::nothrow) u8[buffSize];
    SOCKET sock = client.GetSocketBean().GetSocket();

    if (NULL == pBuff)
    {
        return false;
    }

    // 服务器响应了吗？当第一组数据到达的时候认为服务器响应了
    bool hasResponse = false;

    // 返回数据头部已经全部接受完毕了吗？
    bool hasGetAllResponseHead = false;

    // 记录上一次数据到来的时间
    TimerRecorder dataTimer;

    DogStringA responseHead;
    responseHead.reserve(1024);

    // 已经接受的大小
    u64 hasGetSize = 0;

    while (true)
    {
        if (m_gTimeOut > 0)
        {
            if (gTimer.GetTimePass() >= m_gTimeOut)
            {
                break;
            }
        }

        if (m_dataTimeOut > 0)
        {
            if (dataTimer.GetTimePass() >= m_dataTimeOut)
            {
                break;
            }
        }

        int rcvSize = 0;
        ::memset(pBuff, 0, buffSize);
        rcvSize = ::recv(sock, (char*)pBuff, buffSize, 0);

        if (rcvSize > 0)
        {
            hasResponse = true;
            dataTimer.ReSet();

            // 接受头部,头部以 \r\n\r\n\r\n 结束
            if (!hasGetAllResponseHead)
            {
                int i = 0;
                for (; i < rcvSize; ++i)
                {
                    if (pBuff[i] == '\r')
                    {
                        if (i + 3 < rcvSize &&
                            pBuff[i + 1] == '\n' &&
                            pBuff[i + 2] == '\r' &&
                            pBuff[i + 3] == '\n')
                        {
                            hasGetAllResponseHead = true;
                            i += 4;
                            responseHead.append("\r\n\r\n");
                            break;
                        }
                    }

                    responseHead.append(1, pBuff[i]);
                }

                if (!hasGetAllResponseHead || i >= rcvSize)
                {
                    continue;
                }
                else
                {
                    // 否则将余下的输出
                    rcvSize -= i;
                    ::memcpy(pBuff, pBuff + i, rcvSize);
                    ::memset(pBuff + rcvSize, 0, buffSize - rcvSize);
                }
            }
            
            hasGetSize += rcvSize;
            if (m_downLoadPercentCallBack)
            {
                m_downLoadPercentCallBack(hasGetSize, 0);
            }

            if (m_downLoadLoadStream)
            {
                m_downLoadLoadStream->Write(pBuff, rcvSize);
            }
        }
        else if (rcvSize == 0)
        {
            // 等于0 说明接受完成了
            break;
        }
        else
        {
            // 服务器还没有响应 ||
            // 缓冲区繁忙 WSAGetLastError 函数是本线程中的所有socket，所以不会有多线程问题
            // 我们先等着
            if (!hasResponse || 
                ::WSAGetLastError() == WSAEWOULDBLOCK)
            {
                ::Sleep(1);
                continue;
            }

            break;
        }
    }

    delete[]pBuff;
    pBuff = NULL;
    return true;
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

void SocketHttpClient::SetGTimeOut(u32 timeOut)
{
    m_gTimeOut = timeOut;
}

void SocketHttpClient::SetDataTimeOut(u32 timeOut)
{
    m_dataTimeOut = timeOut;
}
