#include "HeaderShare.h"

bool SocketUtil::StaticInit()
{
#if _WIN32
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        ReportError("Starting Up");
        return false;
    }
#endif
    return true;
}

void SocketUtil::CleanUp()
{
#if _WIN32
    WSACleanup();
#endif
}

void SocketUtil::ReportError(const char* inOperationDesc)
{
#if _WIN32
    LPVOID lpMsgBuf;
    DWORD errorNum = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorNum,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);

    LOG("Error %s: %d- %s", inOperationDesc, errorNum, lpMsgBuf);
#else
    LOG("Error: %hs", inOperationDesc);
#endif
}

SocketError SocketUtil::GetLastError()
{
#if _WIN32
    return WSAGetLastError();
#else
    return errno;
#endif
}

TCPSocketPtr SocketUtil::CreateTCPSocket(SocketAddressFamily inFamily)
{
    // IP类型，有序缓存，TCP类型
    SOCKET s = socket(inFamily, SOCK_STREAM, IPPROTO_TCP);
    if (s != INVALID_SOCKET) {
        return TCPSocketPtr(new TCPSocket(s));
    }

    ReportError("SocketUtil::CreateTCPSocket");
    return nullptr;
}

UDPSocketPtr SocketUtil::CreateUDPSocket(SocketAddressFamily inFamily)
{
    // IP类型，离散缓存，UDP类型
    SOCKET s = socket(inFamily, SOCK_DGRAM, IPPROTO_UDP);
    if (s != INVALID_SOCKET) {
        // 这里之前犯病用了make_share直接析构关闭了我的socket
        return UDPSocketPtr(new UDPSocket(s));
    }

    ReportError("SocketUtil::CreateUDPSocket");
    return nullptr;
}
