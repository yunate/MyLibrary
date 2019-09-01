#include "SocketUdpServer.h"

SocketUdpServer::SocketUdpServer(const std::string& ip, unsigned short port)
{
    if (!Init(SOCKET_DGRAM, IPPROTOCOL_UDP))
    {
        return;
    }

    GetSocketBean().SetIpAddress(ip);
    GetSocketBean().SetPort(port);
    SOCKADDR socketAddr;
    GetSocketBean().GetSOCKADDR(socketAddr);

    if (0 != ::bind(GetSocketBean().GetSocket(), &socketAddr, sizeof(socketAddr)))
    {
        return;
    }
}

SocketUdpServer::~SocketUdpServer()
{
}
