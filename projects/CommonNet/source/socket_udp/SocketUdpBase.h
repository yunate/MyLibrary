
#ifndef __SOCKET_UDP_BASE_H_
#define __SOCKET_UDP_BASE_H_

#include "socket_common/SocketBase.h"


class SocketUdpBase :
    public SocketBase
{
public:
    /** 构造函数
    */
    SocketUdpBase();

    /** 析构函数
    */
    virtual ~SocketUdpBase();

public:
    /** 发送消息 当msg大于大约 1K时候返回的值可能不等于msg的值（一次性发送不了）
    @param [in] ip 目标ip
    @param [in] port 目标port
    @param [in] msg 希望发送的消息
    @return 成功返回发送的个数，失败返回SOCKET_ERROR
    */
    virtual int SendMsg(const std::string& ip, unsigned short port, const std::string & msg);

    /** 发送消息 当msg大于大约 1K时候返回的值可能不等于msg的值（一次性发送不了）
    @param [in] sockAddr 目标sockAddr
    @param [in] msg 希望发送的消息
    @return 成功返回发送的个数，失败返回SOCKET_ERROR
    */
    virtual int SendMsg(const SOCKADDR& sockAddr, const std::string & msg);

    /** 接收消息
    @param [out] ip 目标ip
    @param [out] port 目标port
    @param [out] msg 收到的消息
    @return 成功返回接受的个数，失败返回SOCKET_ERROR
    */
    virtual int RcvMsg(std::string & msg, std::string& ip, unsigned short& port);

    /** 接收消息
    @param [out] sockAddr 目标sockAddr
    @param [out] msg 收到的消息
    @return 成功返回接受的个数，失败返回SOCKET_ERROR
    */
    virtual int RcvMsg(std::string & msg, SOCKADDR& sockAddr);
};

#endif // __SOCKET_UDP_BASE_H_

