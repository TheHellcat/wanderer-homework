// Programmer Homework - by Michael "HELLCAT"

#include "Error.h"

using namespace std;

Error::Error(string moduleName)
{
    callingModuleName = moduleName;
    loggedErrorCount = 0;
}

void Error::LogWarning(string message)
{
    Log("Warning", message);
}

void Error::LogError(string message)
{
    Log("ERROR", message);
}

void Error::Log(string severity, string message)
{
    loggedErrorCount++;
    printf("[%s] (%03d) %s: %s\n", callingModuleName.c_str(), loggedErrorCount, severity.c_str(), message.c_str());
}
