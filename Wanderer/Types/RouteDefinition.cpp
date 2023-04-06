// Programmer Homework - by Michael "HELLCAT"

#include "RouteDefinition.h"

RouteDefinition::RouteDefinition()
{
    stopCount = 0;
    dayCount = 0;
    distances = nullptr;
    currentDistanceIdx = 0;
    manualDistances = false;
    errorLogger = new Error("RouteDefinition");
}

RouteDefinition::RouteDefinition(int inStopCount)
{
    stopCount = inStopCount;
    dayCount = 0;
    distances = new int[inStopCount];
    currentDistanceIdx = 0;
    manualDistances = false;
    errorLogger = new Error("RouteDefinition");

    ClearDistances();
}

RouteDefinition::~RouteDefinition()
{
    if ((!manualDistances) && (distances != nullptr))
    {
        delete distances;
    }

    delete errorLogger;
}

void RouteDefinition::ClearDistances()
{
    int i;

    if (distances == nullptr)
    {
        errorLogger->LogWarning("Attempt to clear uninitialised distance array");
        return;
    }

    for (i = 0; i < stopCount; i++)
    {
        distances[i] = 1;
    }

    currentDistanceIdx = 0;
}

void RouteDefinition::AddNextDistance(int distance)
{
    if (currentDistanceIdx == stopCount)
    {
        errorLogger->LogWarning("Attempt to add to distance array beyond given stop count");
        return;
    }

    distances[currentDistanceIdx] = distance;
    currentDistanceIdx++;
}

int RouteDefinition::GetStopCount()
{
    return stopCount;
}

void RouteDefinition::SetDayCount(int days)
{
    dayCount = days;
}

int RouteDefinition::GetDayCount()
{
    return dayCount;
}

int RouteDefinition::GetDistance(int Idx)
{
    if ((Idx > (stopCount - 1)) || (Idx < 0) || (distances == nullptr))
    {
        char msg[128];
        int r;

        r = sprintf_s(msg, 128, "Attempt to get distance beyond array bounds (index %d was requested)", Idx);

        if (r > 0)
        {
            errorLogger->LogWarning(msg);
        }

        return 0;
    }

    return distances[Idx];
}
