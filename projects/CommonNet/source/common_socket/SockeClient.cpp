#include "SockeClient.h"

Socket_client::Socket_client()
{
}

Socket_client::~Socket_client()
{
}

bool Socket_client::Connect(const SOCKADDR & socketAddr)
{
    if (!GetSocketNode().IsValidSocket())
    {
        return false;
    }

    GetSocketNode().SetSOCKADDR(socketAddr);
    return (0 == ::connect(GetSocketNode().GetSocket(), &socketAddr, sizeof(socketAddr)));
}

bool Socket_client::Connect(const std::string & address, unsigned short port)
{
    if (!GetSocketNode().IsValidSocket())
    {
        return false;
    }

    GetSocketNode().SetIpAddress(address);
    GetSocketNode().SetPort(port);
    SOCKADDR socketAddr;
    GetSocketNode().GetSOCKADDR(socketAddr);
    return (0 == ::connect(GetSocketNode().GetSocket(), &socketAddr, sizeof(socketAddr)));
}
