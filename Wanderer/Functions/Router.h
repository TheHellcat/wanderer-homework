// Programmer Homework - by Michael "HELLCAT"

#pragma once

#include "Error.h"
#include "../Types/RouteDefinition.h"

class Router
{
public:
    Router();
    ~Router();
    void FindBestRoute(RouteDefinition* inRoute, int*& outDailyDistances, int& outMaxDistance);

private:
    Error* errorLogger;

    bool AdjustStopOffsets(int* stopOffsets, int dayCount, int currentDay);
};
