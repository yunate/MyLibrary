
#include "Test_Socket.h"
#include "color_print.h"
#include "http/socket_http/SocketHttpClient.h"
#include "http/socket_http/HttpUtil.h"

void Test_Tcp_Client()
{
    SocketTcpClient client("127.0.0.1", (unsigned short)10001);

    if (!client.Connect())
    {
        return;
    }

    client.SendMsg("hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word"
                   "hello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello wordhello word");
}

void Test_Tcp_Server()
{
    SocketTcpServer server("0", (unsigned short)10001);

    if (!server.Listen(20))
    {
        return;
    }

    std::shared_ptr<SocketTcpBase> spClient = server.Accept();

    if (spClient != NULL)
    {
        std::string msg;
        // spClient->RcvMsg(msg);
        spClient->RcvMsg([&msg](char* buff, unsigned int buffSize)
                         {
                             msg.append(buff, buffSize);
                             // 如果想手动结束的话，返回false 
                             return true; 
                         });
        ColorPrintf(Green, msg.c_str());
        ::printf("\r\n");
    }
}

void Test_Udp_Client()
{
    SocketUdpClient client;
    client.SendMsg("127.0.0.1", (unsigned short)10001, "hello word");
}

void Test_Udp_Server()
{
    SocketUdpServer server("0", (unsigned short)10001);
    std::string msg;
    std::string ip;
    unsigned short port;

    if (SOCKET_ERROR != server.RcvMsg(msg, ip, port))
    {
        ColorPrintf(Green, msg.c_str());
        ::printf("\r\n");
    }
}

void Test_Http_Get()
{
    DogStringA out;
    SPHttpClient httpGet = HttpUtils::CreateHttpGet("http://stool.chinaz.com/same?s=ip.tool.chinaz.com&page=");

    if (httpGet == NULL)
    {
        return;
    }

    // 你可以将这个放到线程中去
    bool res = httpGet->MakeRequest();

    SPResponse response = httpGet->GetResponse();
    SPDogStream responseStream = response->GetStream();
    int statucCode = response->GetStatusCode();

    if (res && statucCode >= 200 && statucCode <= 300)
    {
        s64 size = responseStream->Size();
        out.resize((size_t)size);
        responseStream->ReadAllA((u8*)out.c_str());
    }
    else
    {
        DogStringA body;
        s64 size = responseStream->Size();
        body.resize((size_t)size);
        responseStream->ReadAllA((u8*)body.c_str());
        out = response->GetRawHead();
        out += body;
    }
}

void Test_Http_Download()
{
    SPHttpClient httpDown = 
        HttpUtils::CreateHttpDownload("",
                                      _DogT("F:\\test\\down\\"));
    bool res = httpDown->MakeRequest();
    SPResponse response = httpDown->GetResponse();
    int statucCode = response->GetStatusCode();
}

