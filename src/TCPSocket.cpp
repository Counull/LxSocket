#include "HeaderShare.h"

TCPSocket::~TCPSocket()
{
    closesocket(mSocket);
}

std::expected<int, SocketError> TCPSocket::Connect(const SocketAddress& inAddress)
{
    auto err = connect(mSocket, &inAddress.mSocketAddr, inAddress.GetSize());
    if (err < 0) {
        SocketUtil::ReportError("TCPSocket::Connect");
        return std::unexpected(SocketUtil::GetLastError());
    }
    

    return NO_ERROR;
}

std::expected<int, SocketError> TCPSocket::Bind(const SocketAddress& address)
{
    auto err = bind(mSocket, &address.mSocketAddr, address.GetSize());
    if (err != 0) {
        SocketUtil::ReportError("TCPSocket::Bind");
        return std::unexpected(SocketUtil::GetLastError());
    }
    return NO_ERROR;
}
std::expected<int, SocketError> TCPSocket::Listen(int inBackLog)
{
    auto err = listen(mSocket, inBackLog);
    if (err < 0) {
        SocketUtil::ReportError("TCPSocket::Listen");
        return std::unexpected(SocketUtil::GetLastError());
    }
    return NO_ERROR;
}

std::expected<int, SocketError> TCPSocket::Send(const void* inData, int inLen)
{
    auto byteSendCount = send(mSocket, static_cast<const char*>(inData), inLen, 0);
    if (byteSendCount < 0) {
        SocketUtil::ReportError("TCPSocket::Send");
        return std::unexpected(SocketUtil::GetLastError());
    }
    return byteSendCount;
}

std::expected<int, SocketError> TCPSocket::Recvive(void* inBuffer, int inLen)
{
    auto byteRecvCount = recv(mSocket, static_cast<char*>(inBuffer), inLen, 0);
    if (byteRecvCount < 0) {
        SocketUtil::ReportError("TCPSocket::Recvive");
        return std::unexpected(SocketUtil::GetLastError());
    }
    return byteRecvCount;
}

std::shared_ptr<TCPSocket> TCPSocket::Accept(SocketAddress& inFromAddr)
{
    int length = inFromAddr.GetSize();
    auto newSocket = accept(mSocket, &inFromAddr.mSocketAddr, &length);

    if (newSocket != INVALID_SOCKET) {
        return std::make_shared<TCPSocket>(TCPSocket(newSocket));
    }
    SocketUtil::ReportError("TCPSocket::Accept");
    return nullptr;
}

TCPSocket::TCPSocket(SOCKET inSocket)
    : mSocket(inSocket)
{
}
