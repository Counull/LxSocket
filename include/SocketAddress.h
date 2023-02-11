#ifndef SOCKETADDRESS_H
#define SOCKETADDRESS_H

#pragma once
#define WIN32_LEAN_AND_MEAN

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>
#include <memory>
#include <stdint.h>

class SocketAddress {
public:
    SocketAddress(uint32_t inAddress, uint16_t inProt);
    SocketAddress(const sockaddr& inSockAddr);
    ~SocketAddress();

    inline size_t GetSize() const { return sizeof(sockaddr); }

private:
    friend class UDPSocket;
    
    sockaddr mSocketAddr;
    inline sockaddr_in* GetAsSockAddrIn() { return reinterpret_cast<sockaddr_in*>(&mSocketAddr); };
};
using SocketAddressPtr = std::shared_ptr<SocketAddress>;

#endif