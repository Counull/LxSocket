#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#pragma once

#include "HeaderShare.h"
class UDPSocket {
public:
    ~UDPSocket();
    // std::expected 或许我应该用rust写这玩意
    std::expected<int, SocketError> Bind(const SocketAddress& address);
    std::expected<int, SocketError> SendTo(const void* inData, int inLen, const SocketAddress& sendTo);
    std::expected<int, SocketError> ReciveFrom(void* inBuffer, int inLen, SocketAddress& outFtom);

private:
    friend class SocketUtil;
    UDPSocket(SOCKET inSocket);
    SOCKET mSocket;
};
using UDPSocketPtr = std::shared_ptr<UDPSocket>;
#endif