// Programmer Homework - by Michael "HELLCAT"

#pragma once

#include <string>

class Error
{
public:
    explicit Error(std::string moduleName);
    void LogWarning(std::string message);
    void LogError(std::string message);

private:
    std::string callingModuleName;
    int loggedErrorCount;

    void Log(std::string severity, std::string message);
};
