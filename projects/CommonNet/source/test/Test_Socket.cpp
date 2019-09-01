
#include "Test_Socket.h"
#include "color_print.h"

void Test_Tcp_Client()
{
    SocketTcpClient client("127.0.0.1", (unsigned short)10001);

    if (!client.Connect())
    {
        return;
    }

    client.SendMsg("hello word");
}

void Test_Tcp_Server()
{
    SocketTcpServer server("0", (unsigned short)10001);

    if (!server.Listen(20))
    {
        return;
    }

    SocketTcpBase* pClient = server.Accept();

    if (pClient != NULL)
    {
        std::string msg;
        pClient->RcvMsg(msg);
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

