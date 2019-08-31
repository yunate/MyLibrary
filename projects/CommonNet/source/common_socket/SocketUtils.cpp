
#include "SocketUtils.h"
#include <WINSOCK2.H>

bool SocketUtils::GetHostName(std::string& name)
{
    char buff[1024] = {0};
    return (SOCKET_ERROR != ::gethostname(buff, sizeof(buff)));
}

hostent* SocketUtils::GetHostByName(const std::string & name)
{
   return ::gethostbyname(name.c_str());
}
