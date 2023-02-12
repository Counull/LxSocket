
#ifndef SOCKETUTIL_H
#define SOCKETUTIL_H

#pragma once
#include "HeaderShare.h"


enum SocketAddressFamily {
    INET = AF_INET,
    INET6 = AF_INET6
};

class SocketUtil {
public:
    static bool StaticInit();
    static void CleanUp();

    static void ReportError(const char* inOperationDesc);
    static SocketError GetLastError();

    static UDPSocketPtr CreateUDPSocket(SocketAddressFamily inFamily);
    static TCPSocketPtr CreateTCPSocket(SocketAddressFamily inFamily);

private:
};
#endif