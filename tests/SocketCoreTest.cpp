#include "HeaderShare.h"
#include "SocketAddress.h"
#include "SocketAddressFactory.h"
#include "SocketUtil.h"
#include <expected>
#include <gtest/gtest.h>
#include <string.h>
#include <synchapi.h>
#include <vcruntime.h>
#include <vcruntime_string.h>

TEST(SocketCore, TestLink)
{
    SocketUtil::StaticInit();
    auto addr = SocketAddressFactory::CreateIPv4FromString("127.0.0.1");
    ASSERT_TRUE(addr.has_value());
    SocketUtil::CleanUp();
    // 资源回收
}

void CreateAddress(SocketAddressPtr& addr, SocketAddressPtr& toRet)
{
    auto opAddr = SocketAddressFactory::CreateIPv4FromString("127.0.0.1");
    auto opToRet = SocketAddressFactory::CreateIPv4FromString("127.0.0.1:51601");
    ASSERT_TRUE(opAddr.has_value());
    ASSERT_TRUE(opToRet.has_value());
    addr = opAddr.value();
    toRet = opToRet.value();
}

TEST(SocketCore, UDPSocket)
{
    SocketUtil::StaticInit();
    auto UDPSocket = SocketUtil::CreateUDPSocket(INET);
    SocketAddressPtr addr;
    SocketAddressPtr toRet;
    CreateAddress(addr, toRet);
    auto ret = UDPSocket->Bind(*addr.get());
    ASSERT_TRUE(ret);
    auto data = "hello udp";
    auto len = strlen(data);
    auto sendLen = UDPSocket->SendTo(data, len, *toRet.get());
    ASSERT_EQ(len, sendLen);
    SocketUtil::CleanUp();
}
TEST(SocketCore, TCPSocket)
{
    SocketUtil::StaticInit();

    auto TCPSocket = SocketUtil::CreateTCPSocket(INET);
    SocketAddressPtr addr;
    SocketAddressPtr toRet;
    CreateAddress(addr, toRet);
    auto ret = TCPSocket->Bind(*addr.get());
    ASSERT_TRUE(ret);
    ret = TCPSocket->Connect(*toRet.get());
    ASSERT_TRUE(ret);
    auto data = "hello tcp";
    auto len = strlen(data);
    Sleep(50);
    auto sendLen = TCPSocket->Send(data, len);
    ASSERT_EQ(len, sendLen);
    constexpr size_t BUFFER_SIZE = 100;
    char buffer[BUFFER_SIZE];

    //  recv test
    // auto recvLen = TCPSocket->Recvive(buffer, BUFFER_SIZE);
    // ASSERT_TRUE(recvLen);
    // auto recvStr = new char[recvLen.value() + 1];
    // recvStr[recvLen.value()] = '\0';
    // memcpy(recvStr, buffer, recvLen.value());
    // std::cout << recvStr << std::endl;
    // delete[] recvStr;

    SocketUtil::CleanUp();
}

TEST(STD, STDTEST)
{
    std::expected<int, int> expected = std::unexpected(5);
    ASSERT_FALSE(expected);
    expected = 5;
    ASSERT_TRUE(expected);
}