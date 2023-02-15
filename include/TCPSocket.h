#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "HeaderShare.h"
#pragma once

class TCPSocket {
public:
    ~TCPSocket();
  
    std::expected<int, SocketError> Connect(const SocketAddress& inAddress);
    std::expected<int, SocketError> Bind(const SocketAddress& inAddress);
    std::expected<int, SocketError> Listen(int inBackLog = 32);
    std::expected<int, SocketError> Send(const void* inData, int inLen);
    std::expected<int, SocketError> Recvive(void* inBuffer, int inLen);
    std::shared_ptr<TCPSocket> Accept(SocketAddress& inFromAddr);

private:
    friend class SocketUtil;
    TCPSocket(SOCKET inSocket);
    SOCKET mSocket;
};
using TCPSocketPtr = std::shared_ptr<TCPSocket>;
#endif