#ifndef PUBLIC_H
#define PUBLIC_H
#pragma once
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "WinSock2.h"
#include "Windows.h"
#include "Ws2tcpip.h"

typedef int socklen_t;
// typedef char* receiveBufer_t;
#else
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// typedef void* receiveBufer_t;
typedef int SOCKET;
const int NO_ERROR = 0;
const int INVALID_SOCKET = -1;
const int WSAECONNRESET = ECONNRESET;
const int WSAEWOULDBLOCK = EAGAIN;
const int SOCKET_ERROR = -1;
#endif

#include <cassert>
#include <deque>
#include <expected>
#include <iostream>
#include <list>
#include <memory>
#include <optional>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using SocketError = int;

#include "SocketAddress.h"
#include "SocketAddressFactory.h"


#include "StringUtils.h"
#include "TCPSocket.h"
#include "UDPSocket.h"
#include "SocketUtil.h"
#endif