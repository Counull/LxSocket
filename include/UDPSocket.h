#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#pragma once


#include <memory>
#include "SocketAddress.h"

class UDPSocket {
public:
    ~UDPSocket();
    int Bind(const SocketAddress& address);
    int SendTo(const void* inData, int inLen, const SocketAddress& sendTo);
    int ReciveFrom(void* inBuffer, int inLen, SocketAddress& outFtom);

private:
    friend class SocketUtil;

    UDPSocket(SOCKET inSocket);
    SOCKET mSocket;
};
using UDPSocketPtr = std::shared_ptr<UDPSocket>;
#endif