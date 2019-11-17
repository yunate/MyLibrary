
#ifndef _SOCKET_HTTP_CLIENT_H__
#define _SOCKET_HTTP_CLIENT_H__

#include "socket_tcp/SocketTcpClient.h"

class SocketHttpClient :
    public SocketTcpClient
{
public:
    /** 构造函数
    */
    SocketHttpClient();

    /** 析构函数
    */
    ~SocketHttpClient();
public:

};


#endif // _SOCKET_HTTP_CLIENT_H__
