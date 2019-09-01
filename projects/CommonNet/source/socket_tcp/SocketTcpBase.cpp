#include "SocketTcpBase.h"

SocketTcpBase::SocketTcpBase()
{
}

SocketTcpBase::~SocketTcpBase()
{
}

int SocketTcpBase::SendMsg(const std::string & msg)
{
    if (GetSocketBean().IsValidSocket())
    {
        return ::send(GetSocketBean().GetSocket(), msg.c_str(), (int)msg.size(), 0);
    }

    return SOCKET_ERROR;
}

int SocketTcpBase::RcvMsg(std::string & msg)
{
    unsigned int buffSize = GetBuffSize();
    char* pBuff = new (std::nothrow) char[buffSize];

    if (NULL == pBuff)
    {
        return SOCKET_ERROR;
    }

    ::memset(pBuff, 0, buffSize);
    int rcvSize = SOCKET_ERROR;

    if (GetSocketBean().IsValidSocket())
    {
        rcvSize = ::recv(GetSocketBean().GetSocket(), pBuff, buffSize, 0);

        if (SOCKET_ERROR != rcvSize)
        {
            msg.reserve(rcvSize);
            msg.append(pBuff, rcvSize);
        }
    }
    
    delete[]pBuff;
    pBuff = NULL;
    return rcvSize;
}
