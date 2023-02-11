
#ifndef SOCKETUTIL_H
#define SOCKETUTIL_H

#pragma once
#include "UDPSocket.h"
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>

enum SocketAddressFamily {
    INET = AF_INET,
    INET6 = AF_INET6
};

class SocketUtil {
public:
    static bool StaticInit();
    static void CleanUp();

    static void ReportError(const char* inOperationDesc);
    static int GetLastError();

    static UDPSocketPtr CreateUDPSocket(SocketAddressFamily inFamily);

private:
};
#endif