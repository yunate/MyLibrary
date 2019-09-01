#include "SocketUdpClient.h"

SocketUdpClient::SocketUdpClient()
{
    if (!Init(SOCKET_DGRAM, IPPROTOCOL_UDP))
    {
        return;
    }
}

SocketUdpClient::~SocketUdpClient()
{
}
