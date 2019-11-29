
#include "Test_Socket.h"
#include "color_print.h"
#include "http/socket_http/SocketHttpClient.h"

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

void Test_Http_client()
{
    SocketHttpClient httpClient;
    httpClient.Get("http://ip.tool.chinaz.com/");
}

