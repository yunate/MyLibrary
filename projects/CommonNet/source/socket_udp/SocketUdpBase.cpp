#include "SocketUdpBase.h"

SocketUdpBase::SocketUdpBase()
{
}

SocketUdpBase::~SocketUdpBase()
{
}

int SocketUdpBase::SendMsg(const std::string& ip, unsigned short port, const std::string & msg)
{
    SocketBean bean;
    bean.SetIpAddress(ip);
    bean.SetPort(port);
    SOCKADDR socketAddr;
    bean.GetSOCKADDR(socketAddr);
    return SendMsg(socketAddr, msg);
}

int SocketUdpBase::SendMsg(const SOCKADDR & sockAddr, const std::string & msg)
{
    if (GetSocketBean().IsValidSocket())
    {
        return ::sendto(GetSocketBean().GetSocket(), msg.c_str(), (int)msg.size(), 0, &sockAddr, sizeof(sockAddr));
    }

    return SOCKET_ERROR;
}

int SocketUdpBase::RcvMsg(std::string & msg, std::string& ip, unsigned short& port)
{
    SOCKADDR sockAddr;
    int rtn = RcvMsg(msg, sockAddr);

    if (SOCKET_ERROR == rtn)
    {
        return rtn;
    }

    SocketBean bean;
    bean.SetSOCKADDR(sockAddr);
    bean.GetIpAddress(ip);
    bean.GetPort(port);
    return rtn;
}

int SocketUdpBase::RcvMsg(std::string & msg, SOCKADDR & sockAddr)
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
        int size = sizeof(SOCKADDR);
        SOCKADDR socketAddr;
        rcvSize = ::recvfrom(GetSocketBean().GetSocket(), pBuff, buffSize, 0, &socketAddr, &size);

        if (SOCKET_ERROR != rcvSize)
        {
            sockAddr = socketAddr;
            msg.reserve(rcvSize);
            msg.append(pBuff, rcvSize);
        }
    }

    delete[]pBuff;
    pBuff = NULL;
    return rcvSize;
}
