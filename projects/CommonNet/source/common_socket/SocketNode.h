
#ifndef __SOCKET_NODE_H_
#define __SOCKET_NODE_H_

#include <string>
#include <WINSOCK2.H>

/** socket数据传输类型
*/
enum SocketType
{
    /** 字节流，比如TCP
    */
    SOCKET_STREAM = 1,

    /** 离散数据，比如UDP
    */
    SOCKET_DGRAM = 2
};

/** 协议，目前只提供tcp，udp
*/
enum IpProtocolType
{
    /** TCP
    */
    IPPROTOCOL_TCP = 6,

    /** UDP
    */
    IPPROTOCOL_UDP = 17
};


class SocketNode
{
public:
    SocketNode() :
        m_socket(INVALID_SOCKET),
        m_ipAddress(""),
        m_port(0)
    {

    }

public:
    /** socket 是否有效
    return 是否有效
    */
    inline bool IsValidSocket() const
    {
        return (INVALID_SOCKET != m_socket);
    }

    /** 获得socket
    return socket
    */
    SOCKET GetSocket() const
    {
        return m_socket;
    }

    /** 设置socket
    @param [in] socket
    */
    inline void SetSocket(SOCKET socket)
    {
        m_socket = socket;
    }

    /** 获得IP地址，对于不同的socket有着不同的意义，
    @param [out] ipAddress ip地址
    */
    inline void GetIpAddress(std::string& ipAddress) const
    {
        ipAddress = m_ipAddress;
    }

    /** 设置IP地址，仅仅是设置而已
    @param [in] ipAddress ip地址
    */
    inline void SetIpAddress(const std::string& ipAddress)
    {
        m_ipAddress = ipAddress;
    }

    /** 获得端口，对于不同的socket有着不同的意义，
    @param [out] port 端口
    */
    inline void GetPort(unsigned short & port) const
    {
        port = m_port;
    }

    /** 设置端口，仅仅是设置而已
    @param [in] port 端口
    */
    inline void SetPort(unsigned short port)
    {
        m_port = port;
    }

    /** 获得SOCKADDR，对于不同的socket有着不同的意义，
    @param [out] socketAddr SOCKADDR
    */
    inline void GetSOCKADDR(SOCKADDR& socketAddr) const
    {
        sockaddr_in* pPockAddr = (sockaddr_in*)(&socketAddr);
        memset(pPockAddr, 0, sizeof(sockaddr_in));
        pPockAddr->sin_family = PF_INET;
        pPockAddr->sin_addr.s_addr = inet_addr(m_ipAddress.c_str());
        pPockAddr->sin_port = htons(m_port);
    }

    /** 设置SOCKADDR
    @param [in] socketAddr SOCKADDR
    */
    inline void SetSOCKADDR(const SOCKADDR& socketAddr)
    {
        sockaddr_in* pPockAddr = (sockaddr_in*)(&socketAddr);
        m_ipAddress = inet_ntoa(pPockAddr->sin_addr);
        m_port = pPockAddr->sin_port;
    }

private:
    /** 套接字
    */
    SOCKET m_socket;

    /** ip地址，对于不同的socket有着不同的意义，
        比如服务器的socket这个字段没有实际意义
        比如客户端的socket这个字段表示他链接的服务器地址
    */
    std::string m_ipAddress;

    /** 端口
    */
    unsigned short m_port;
};

#endif //__SOCKET_NODE_H_
