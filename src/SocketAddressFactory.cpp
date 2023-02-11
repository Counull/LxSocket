
#include <memory>
#include <optional>
#include <utility>
#include <vcruntime_string.h>
#include "SocketAddressFactory.h"
using namespace std;
std::optional<SocketAddressPtr> SocketAddressFactory::CreateIPv4FromString(const std::string& inString)
{
    auto pos = inString.find_last_of(':');
    string host, service;
    if (pos != string::npos) {
        host = inString.substr(0, pos);
        service = inString.substr(pos + 1);
    } else {
        host = inString;
        service = "0";
    }

    addrinfo hint;
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;

    addrinfo* result;
    int error = getaddrinfo(host.c_str(), service.c_str(), &hint, &result);

    using deleter = void (*)(addrinfo*);
    unique_ptr<addrinfo, deleter> pResult(result, [](auto p) {
        freeaddrinfo(p);
    });

    // 如果有错误但返回了AddrInfo
    if (error != 0) {
        return nullopt;
    }

    while (!result->ai_addr && result->ai_next) {
        result = result->ai_next;
    }

    if (!result->ai_addr) {
        return nullopt;
    }

    auto toRet = std::make_shared<SocketAddress>(*result->ai_addr);

    return std::make_optional(std::move(toRet));
}
