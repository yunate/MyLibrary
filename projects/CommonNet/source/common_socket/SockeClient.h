
#ifndef __SOCKET_CLINT_H_
#define __SOCKET_CLINT_H_

#include "SocketBase.h"

class Socket_client :
    public SocketBase
{
public:
    /** 构造函数
    */
    Socket_client();

    /** 析构函数
    */
    virtual ~Socket_client();

public:
    /** 连接到 [服务器等]
    param [in] socketAddr 包含了ip和端口
    @return 是否成功
    */
    bool Connect(const SOCKADDR& socketAddr);

    /** 连接到 [服务器等]
    param [in] address ip地址
    param [in] port 端口
    @return 是否成功
    */
    bool Connect(const std::string& address, unsigned short port);
};

#endif //__SOCKET_CLINT_H_
