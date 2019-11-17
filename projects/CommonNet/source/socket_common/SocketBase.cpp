#include "SocketBase.h"

SocketBase::SocketBase() :
    m_buffSize(1025)
{
}

bool SocketBase::Init(SocketType type, IpProtocolType ipProto)
{
    GetSocketBean().SetSocket(::socket(PF_INET, (int)type, (int)ipProto));
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
