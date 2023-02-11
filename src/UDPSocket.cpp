#include "UDPSocket.h"

UDPSocket::~UDPSocket()
{
}
int UDPSocket::Bind(const SocketAddress& address)
{
    int err = bind(mSocket, &address.mSocketAddr, address.GetSize());
    if (err!=0){
        
    }
}
