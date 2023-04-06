// Programmer Homework - by Michael "HELLCAT"

#pragma once

#include "../Types/RouteDefinition.h"

class FileIo
{
public:
    FileIo();
    ~FileIo();
    RouteDefinition* ReadRouteDefinitionFromFile(std::string fileName);

private:
    Error* errorLogger;
};
