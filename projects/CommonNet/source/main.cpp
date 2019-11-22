
#include "test\Test_Socket.h"
#include "test\TestUrl.h"

int main()
{
    TestUrl();
    return 1;
    WSADATA wsaData = { 0 };
    int iResult = ::WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (iResult)
    {

    }

    Test_Tcp_Server();
    // Test_Tcp_Client();

    // Test_Udp_Server();
    // Test_Udp_Client();
    ::WSACleanup();
    ::system("pause");
    return 1;
}
