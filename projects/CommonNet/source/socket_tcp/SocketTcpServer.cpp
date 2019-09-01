
#include "SocketTcpServer.h"

SocketTcpServer::SocketTcpServer(const std::string & ip, unsigned short port)
{
    GetSocketBean().SetIpAddress(ip);
    GetSocketBean().SetPort(port);
}

SocketTcpServer::~SocketTcpServer()
{
}

bool SocketTcpServer::Listen(unsigned int backlog)
{
    if (!Init(SOCKET_STREAM, IPPROTOCOL_TCP))
    {
        return false;
    }

    SOCKADDR socketAddr;
    GetSocketBean().GetSOCKADDR(socketAddr);

    if (0 != ::bind(GetSocketBean().GetSocket(), &socketAddr, sizeof(socketAddr)))
    {
        return false;
    }

    return (0 == ::listen(GetSocketBean().GetSocket(), backlog));
}

SocketTcpBase * SocketTcpServer::Accept()
{
    if (!GetSocketBean().IsValidSocket())
    {
        return false;
    }

    SOCKADDR addr;
    int size = sizeof(SOCKADDR);
    SOCKET clientSocket = ::accept(GetSocketBean().GetSocket(), &addr, &size);

    if (INVALID_SOCKET == clientSocket)
    {
        return NULL;
    }

    SocketTcpBase* pClient = new (std::nothrow) SocketTcpBase();

    if (NULL == pClient)
    {
        return NULL;
    }

    pClient->GetSocketBean().SetSOCKADDR(addr);
    pClient->GetSocketBean().SetSocket(clientSocket);
    return pClient;
}
