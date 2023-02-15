#include "HeaderShare.h"

UDPSocket::~UDPSocket()
{
#if _WIN32
    closesocket(mSocket);
#else
    close(mSocket);
#endif
}
UDPSocket::UDPSocket(SOCKET inSocket)
    : mSocket(inSocket)
{
}

std::expected<int, SocketError> UDPSocket::Bind(const SocketAddress& address)
{
    int err = bind(mSocket, &address.mSocketAddr, address.GetSize());
    if (err != 0) {
        SocketUtil::ReportError("UDPSocket::Bind");
        return std::unexpected(SocketUtil::GetLastError());
    }
    return NO_ERROR;
}

std::expected<int, SocketError> UDPSocket::SendTo(const void* inData, int inLen, const SocketAddress& sendTo)
{
    int byteSendCount = sendto(mSocket, static_cast<const char*>(inData), inLen, 0, &sendTo.mSocketAddr, sendTo.GetSize());
    if (byteSendCount >= 0) {
        return byteSendCount;
    }

    SocketUtil::ReportError("UDPSocket::SendTo");
    return std::unexpected(SocketUtil::GetLastError());
}

std::expected<int, SocketError> UDPSocket::ReciveFrom(void* inBuffer, int inLen, SocketAddress& outFrom)
{
    socklen_t fromLen = outFrom.GetSize();
    int readByteCount = recvfrom(mSocket, static_cast<char*>(inBuffer), inLen, 0, &outFrom.mSocketAddr, &fromLen);
    if (readByteCount >= 0) {
        return readByteCount;
    }
    SocketUtil::ReportError("UDPSocket::ReciveFrom");
    return std::unexpected(SocketUtil::GetLastError());
}

std::expected<int, SocketError> UDPSocket::setNoneBlockMode(bool shouldBeNonBlocking)
{

#if _WIN32
    u_long arg = shouldBeNonBlocking ? 1 : 0;
    int result = ioctlsocket(mSocket, FIONBIO, &arg);
#else
    int flags = fcntl(mSocket, F_GETFL, 0);
    flags = shouldBeNonBlocking ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
    int result = fcntl(mSocket, F_SETFL, flags);
#endif

    if (result == SOCKET_ERROR) {
        SocketUtil::ReportError("UDPSocket::setNoneBlockMode");
        return std::unexpected(SocketUtil::GetLastError());
    }
    return NO_ERROR;
}
