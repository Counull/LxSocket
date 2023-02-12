#ifndef SOCKETADDRESS_H
#define SOCKETADDRESS_H

#pragma once

#include "HeaderShare.h"

class SocketAddress {
public:
    SocketAddress(uint32_t inAddress, uint16_t inProt);
    SocketAddress(const sockaddr& inSockAddr);
    ~SocketAddress();

    inline size_t GetSize() const { return sizeof(sockaddr); }

private:
    friend class UDPSocket;
    friend class TCPSocket;
    sockaddr mSocketAddr;
    inline sockaddr_in* GetAsSockAddrIn() { return reinterpret_cast<sockaddr_in*>(&mSocketAddr); };
};
using SocketAddressPtr = std::shared_ptr<SocketAddress>;
#endif