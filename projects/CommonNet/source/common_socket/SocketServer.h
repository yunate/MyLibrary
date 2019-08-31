
#ifndef __SOCKET_SERVER_H_
#define __SOCKET_SERVER_H_

#include "SocketBase.h"

class SocketServer :
    public SocketBase
{
public:
    /** 构造函数
    */
    SocketServer();

    /** 构造函数
    */
    virtual ~SocketServer();

public:
    /** 绑定
    param [in] socketAddr 包含了ip和端口
    @return 是否成功
    */
    bool Bind(const SOCKADDR& socketAddr);

    /** 绑定 INADDR_ANY 
    param [in] address ip地址
    param [in] port 端口
    @return 是否成功
    */
    bool Bind(const std::string& address, unsigned short port);

    /** listen
    param [in] backlog 是在进入队列中允许的连接数目 大多数系统的允许数目是20，你也可以设置为5到10。
    @return 是否成功
    */
    bool Listen(unsigned int backlog);

    /** 接受连入的client，内部创建SocketBase，需要自己释放
    @return 成功返回新的socket，失败返回NULL
    */
    SocketBase* Accept();
};

#endif //__SOCKET_SERVER_H_
