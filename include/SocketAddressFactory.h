#ifndef SOCLETADDRESSFACTORY_H
#define SOCLETADDRESSFACTORY_H

#pragma once
#include "HeaderShare.h"

class SocketAddressFactory {
public:
    /// 说实话本身SharedPtr就包含可空语义这里使用optional没多大意义
    static std::optional<SocketAddressPtr> CreateIPv4FromString(const std::string& inString);

private:
};

#endif