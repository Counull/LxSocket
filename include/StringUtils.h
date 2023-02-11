
#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#pragma once
#include <string>
namespace StringUtils {
std::string GetCommandLineArg(int inIndex);

std::string Sprintf(const char* inFormat, ...);

void Log(const char* inFormat);
void Log(const char* inFormat, ...);
}

#define LOG(...) StringUtils::Log(__VA_ARGS__);

#endif