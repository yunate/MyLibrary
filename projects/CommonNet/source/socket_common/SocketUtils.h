
#ifndef __SOCKET_UTILS_H_
#define __SOCKET_UTILS_H_

#include <string>

struct hostent;

class SocketUtils
{
public:
    /** 返回程序所运行的机器的主机名字
    @param [out] name 返回你程 序所运行的机器的主机名字
    @return 是否成功
    */
    static bool GetHostName(std::string& name);

    /** 通过机器的主机名字返回机器的IP地址
        h_name – 地址的正式名称。
        h_aliases – 空字节-地址的预备名称的指针。
        h_addrtype –地址类型; 通常是AF_INET。
        h_length – 地址的比特长度。
        h_addr_list – 零字节-主机网络地址指针。网络字节顺序。
        h_addr - h_addr_list中的第一地址。
        gethostbyname() 成功时返回一个指向结构体 hostent 的指针，或者 是个空 (NULL) 指针。
    @param [int] name 返回你程 序所运行的机器的主机名字
    @return hostent
    */
    static hostent* GetHostByName(const std::string& name);
};

#endif //__SOCKET_UTILS_H_
