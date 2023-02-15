
#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#pragma once
#include "HeaderShare.h"
namespace StringUtils {


std::string Sprintf(const char* inFormat, ...);

void Log(const char* inFormat);
void Log(const char* inFormat, ...);
}

#define LOG(...) StringUtils::Log(__VA_ARGS__);

#endif