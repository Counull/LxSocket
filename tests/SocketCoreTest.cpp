#include "SocketAddressFactory.h"
#include <gtest/gtest.h>

TEST(SocketCore, CoreTest)
{
    WSADATA wsaData;
    struct hostent* remoteHost = NULL;
    char szHostName[128] = {};
    int nResult = -1;

    // Initialize Winsock
    //进行一次系统初始化
    nResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (nResult != 0) 
    {
        printf("WSAStartup failed: %d\n", nResult);
        return ;
    }
    //gethostname依赖wind socket
    nResult = gethostname(szHostName, sizeof(szHostName));
    if (nResult == 0)
    {
        printf("gethostname success: %s\n", szHostName);
    } 
    else
    {
        printf("gethostname fail(errcode %lu)...\n",::GetLastError());
    }
   

    std::cout << "**********************" <<std::endl;
    SocketAddressFactory::CreateIPv4FromString("www.baidu.com");
    ASSERT_EQ(1, 1);
     //资源回收
    WSACleanup();
}
