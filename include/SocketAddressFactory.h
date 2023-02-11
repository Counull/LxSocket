#ifndef SOCLETADDRESSFACTORY_H
#define SOCLETADDRESSFACTORY_H



#pragma once
#include "SocketAddress.h"
#include <string>

#include <optional>
class SocketAddressFactory {
public:
    static std::optional<SocketAddressPtr> CreateIPv4FromString(const std::string& inString);

private:
};

#endif