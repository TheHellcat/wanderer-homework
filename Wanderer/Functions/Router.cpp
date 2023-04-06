// Programmer Homework - by Michael "HELLCAT"

#include "Router.h"

Router::Router()
{
    errorLogger = new Error("Router");
}

Router::~Router()
{
    delete errorLogger;
}

/**
 * \brief A simple brute-force "algorithm" that calculates all possible distances at all waypoint/stop vs. travel days combinations
 * and returns the one with the lowest maximum travel distance on a single day
 *
 * \param inRoute The route definition (number of waypoints/stops, number of days to travel and all distances between waypoints/stops)
 * \param outDailyDistances Result array containing the distance to travel for each day
 * \param outMaxDistance Result of the maximum distance for the longest travel day
 *
 * Also, this comment doc-block rather belongs in the .h file, but since is primarily meant for the code reviewer looking at the actual
 * implementation, rather the API of this class, it's here.
 */
void Router::FindBestRoute(RouteDefinition* inRoute, int*& outDailyDistances, int& outMaxDistance)
{
    int* distanceSums;
    int* bestFoundRoute;
    int* stopOffsets;
    int lowestDailyDistance;
    int highestIterationDistance;
    int totalDistance;
    int i;
    int j;
    int c;
    int stops;
    int days;
    int totalOffset;
    bool stillLooking;

    // init some values

    totalDistance = 0;
    stops = inRoute->GetStopCount();
    for (i = 0; i < stops; i++)
    {
        totalDistance += inRoute->GetDistance(i);
    }

    // allocate our working arrays of the proper size
    days = inRoute->GetDayCount();
    distanceSums = new int[days];
    bestFoundRoute = new int[days];
    stopOffsets = new int[days];

    // the very first segmentation of "stops each day", we're gonna check, is 1 single waypoint/rest/stop for every day, except for the last day....
    for (i = 0; i < days - 1; i++)
    {
        stopOffsets[i] = 1;
    }

    // ....the last day gets all the remaining stops
    stopOffsets[days - 1] = stops - (days - 1);

    // now we iterate through all possible combinations, to find the one with lowest max. distance on one day

    lowestDailyDistance = totalDistance;
    stillLooking = true;
    while (stillLooking)
    {
        highestIterationDistance = 0;

        // go through all currently via stop-offsets defined segments of the route, and calc distance per segment (=travel day)
        totalOffset = 0;
        for (j = 0; j < days; j++)
        {
            c = 0;
            for (i = 0; i < stopOffsets[j]; i++)
            {
                c += inRoute->GetDistance(totalOffset);
                totalOffset++;
            }

            distanceSums[j] = c;

            if (c > highestIterationDistance)
            {
                highestIterationDistance = c;
            }
        }

        // if the current segmentation has the lowest maximum distance on a segment, remember it as a potential result
        if (highestIterationDistance < lowestDailyDistance)
        {
            lowestDailyDistance = highestIterationDistance;

            for (i = 0; i < days; i++)
            {
                bestFoundRoute[i] = distanceSums[i];
            }
        }

        // adjust the segmentation offsets for the next check iteration
        stillLooking = AdjustStopOffsets(stopOffsets, days, 0);
    }

    // seems we're done, set the output values and off we go
    outDailyDistances = bestFoundRoute;
    outMaxDistance = lowestDailyDistance;
}

bool Router::AdjustStopOffsets(int* stopOffsets, int dayCount, int currentDay)
{
    int i;

    if (currentDay >= dayCount - 1)
    {
        // fun fact, this comment only makes sense, once you've read the one further down (sometimes recursion is a bit like time travel):
        // stand down red alert!
        // (If the to be processed day reached the last one (which gets adjusted in tandem with all the others, already),
        // we're at the end - signal no more segmentation combinations are possible, which will also end the main checking loop in FindBestRoute().)
        return false;
    }

    if (stopOffsets[dayCount - 1] > 1)
    {
        // here we give the current day of travel one waypoint/stop more, but to keep to the correct total amount of stops the last days gets one taken away
        stopOffsets[currentDay]++;
        stopOffsets[dayCount - 1]--;
    }
    else
    {
        // the current day of travel has reached the maximum possible number of stops, so we need to adjust the next one and reset this one to 1.
        // since due to the ++ and -- nature of the adjustments, the current and the last day basically swap their values, so we can simply
        // swap them back and save us some actual calculations, then move to the next day, to adjust the amount of stops for that.
        i = stopOffsets[dayCount - 1];
        stopOffsets[dayCount - 1] = stopOffsets[currentDay];
        stopOffsets[currentDay] = i;

        // RED ALERT! Engage recursion!
        return AdjustStopOffsets(stopOffsets, dayCount, currentDay + 1);
    }

    // if all went well (i.e. we didn't end up in any other branch, above, signal green light to continue checking
    return true;
}
