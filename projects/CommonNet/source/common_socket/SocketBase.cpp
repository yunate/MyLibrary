#include "SocketBase.h"

SocketBase::SocketBase() :
    m_buffSize(1025)
{
}

bool SocketBase::Init(SocketType type, IpProtocolType ipProto)
{
    GetSocketNode().SetSocket(::socket(PF_INET, type, ipProto));
    return GetSocketNode().IsValidSocket();
}

bool SocketBase::UnInit()
{
    if (GetSocketNode().IsValidSocket())
    {
        return (SOCKET_ERROR != ::closesocket(GetSocketNode().GetSocket()));
    }

    return false;
}

int SocketBase::SendMsg(const SocketNode& toSocket, const std::string & msg)
{
    if (toSocket.IsValidSocket())
    {
        return ::send(toSocket.GetSocket(), msg.c_str(), msg.size(), 0);
    }
    else
    {
        SOCKADDR socketAddr;
        toSocket.GetSOCKADDR(socketAddr);
        return ::sendto(toSocket.GetSocket(), msg.c_str(), msg.size(), 0, &socketAddr, sizeof(socketAddr));
    }
}

int SocketBase::RcvMsg(SocketNode& fromSocket, std::string & msg)
{
    char* pBuff = new (std::nothrow) char[m_buffSize];

    if (NULL == pBuff)
    {
        return SOCKET_ERROR;
    }

    int rcvSize = SOCKET_ERROR;

    if (fromSocket.IsValidSocket())
    {
        rcvSize = ::recv(fromSocket.GetSocket(), pBuff, m_buffSize, 0);
    }
    else
    {
        SOCKADDR socketAddr;
        int size = 0;
        rcvSize = ::recvfrom(GetSocketNode().GetSocket(), pBuff, m_buffSize, 0, &socketAddr, &size);
        fromSocket.SetSOCKADDR(socketAddr);
    }

    msg.resize(rcvSize);
    msg.append(pBuff, rcvSize);
    delete[]pBuff;
    pBuff = NULL;
    return rcvSize;
}

bool SocketBase::GetPeerName(SocketNode & fromSocket)
{
    if (!GetSocketNode().IsValidSocket())
    {
        return false;
    }

    SOCKADDR addr;
    int size = 0;

    if (SOCKET_ERROR == ::getpeername(GetSocketNode().GetSocket(), &addr, &size))
    {
        return false;
    }

    fromSocket.SetSOCKADDR(addr);
}
