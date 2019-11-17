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
    if (!Init(SocketType::SOCKET_STREAM, IpProtocolType::IPPROTOCOL_TCP))
    {
        return false;
    }

    SOCKADDR socketAddr;
    GetSocketBean().GetSOCKADDR(socketAddr);
    return (0 == ::connect(GetSocketBean().GetSocket(), &socketAddr, sizeof(socketAddr)));
}
