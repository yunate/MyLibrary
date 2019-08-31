#include "SocketServer.h"

SocketServer::SocketServer()
{
}

SocketServer::~SocketServer()
{
}

bool SocketServer::Bind(const SOCKADDR& socketAddr)
{
    if (!GetSocketNode().IsValidSocket())
    {
        return false;
    }

    GetSocketNode().SetSOCKADDR(socketAddr);
    return (0 == ::bind(GetSocketNode().GetSocket(), &socketAddr, sizeof(socketAddr)));
}

bool SocketServer::Bind(const std::string & address, unsigned short port)
{
    if (!GetSocketNode().IsValidSocket())
    {
        return false;
    }

    GetSocketNode().SetIpAddress(address);
    GetSocketNode().SetPort(port);
    SOCKADDR socketAddr;
    GetSocketNode().GetSOCKADDR(socketAddr);
    return (0 == ::bind(GetSocketNode().GetSocket(), &socketAddr, sizeof(socketAddr)));
}

bool SocketServer::Listen(unsigned int backlog)
{
    if (!GetSocketNode().IsValidSocket())
    {
        return false;
    }

    return (0 == ::listen(GetSocketNode().GetSocket(), backlog));
}

SocketBase* SocketServer::Accept()
{
    if (!GetSocketNode().IsValidSocket())
    {
        return false;
    }

    SOCKADDR addr;
    int size;
    SOCKET clientSocket = ::accept(GetSocketNode().GetSocket(), &addr, &size);

    if (INVALID_SOCKET == clientSocket)
    {
        return NULL;
    }

    SocketBase* pClient = new (std::nothrow) SocketBase();

    if (NULL == pClient)
    {
        return NULL;
    }

    pClient->GetSocketNode().SetSOCKADDR(addr);
    pClient->GetSocketNode().SetSocket(clientSocket);
    return pClient;
}
