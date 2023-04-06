// Programmer Homework - by Michael "HELLCAT"

#pragma once

#include "../Functions/Error.h"

class RouteDefinition
{
public:
    RouteDefinition();
    explicit RouteDefinition(int inStopCount);
    ~RouteDefinition();

    int GetStopCount();
    void SetDayCount(int days);
    int GetDayCount();

    void ClearDistances();
    void AddNextDistance(int distance);
    int GetDistance(int Idx);

private:
    int stopCount;
    int dayCount;
    int* distances;
    int currentDistanceIdx;
    bool manualDistances;
    Error* errorLogger;
};
