
#include "test\Test_Socket.h"

int main()
{
    WSADATA wsaData = { 0 };
    int iResult = 0;
    iResult = ::WSAStartup(MAKEWORD(2, 2), &wsaData);
    // Test_Tcp_Server();
    // Test_Tcp_Client();

    Test_Udp_Server();
    // Test_Udp_Client();
    ::WSACleanup();
    ::system("pause");
    return 1;
}
