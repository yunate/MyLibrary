#include "SocketTcpClient.h"

SocketTcpClient::SocketTcpClient(const std::string& ip, unsigned short port)
{
    GetSocketBean().SetIpAddress(ip);
    GetSocketBean().SetPort(port);
}

SocketTcpClient::~SocketTcpClient()
{
}

bool SocketTcpClient::Connect()
{
    if (!Init(SOCKET_STREAM, IPPROTOCOL_TCP))
    {
        return false;
    }

    SOCKADDR socketAddr;
    GetSocketBean().GetSOCKADDR(socketAddr);
    return (0 == ::connect(GetSocketBean().GetSocket(), &socketAddr, sizeof(socketAddr)));
}
