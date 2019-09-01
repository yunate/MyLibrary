#include "SocketBase.h"

SocketBase::SocketBase() :
    m_buffSize(1025)
{
}

bool SocketBase::Init(SocketType type, IpProtocolType ipProto)
{
    GetSocketBean().SetSocket(::socket(PF_INET, type, ipProto));
    return GetSocketBean().IsValidSocket();
}

bool SocketBase::UnInit()
{
    if (GetSocketBean().IsValidSocket())
    {
        return (SOCKET_ERROR != ::closesocket(GetSocketBean().GetSocket()));
    }

    return false;
}

bool SocketBase::GetPeerName(SocketBean & fromSocket)
{
    if (!GetSocketBean().IsValidSocket())
    {
        return false;
    }

    SOCKADDR addr;
    int size = 0;

    if (SOCKET_ERROR == ::getpeername(GetSocketBean().GetSocket(), &addr, &size))
    {
        return false;
    }

    fromSocket.SetSOCKADDR(addr);
    return true;
}
