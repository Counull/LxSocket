#include "HeaderShare.h"
SocketAddress::SocketAddress(uint32_t inAddress, uint16_t inProt)
    : mSocketAddr { .sa_family = AF_INET }
{
    memset(GetAsSockAddrIn()->sin_zero, 0, sizeof(GetAsSockAddrIn()->sin_zero));
    GetAsSockAddrIn()->sin_addr.S_un.S_addr = htonl(inAddress);
    GetAsSockAddrIn()->sin_port = htons(inProt);
}

SocketAddress::SocketAddress(const sockaddr& inSockAddr)
{

    memcpy(&mSocketAddr, &inSockAddr, sizeof(sockaddr));
}

SocketAddress::~SocketAddress()
{
}