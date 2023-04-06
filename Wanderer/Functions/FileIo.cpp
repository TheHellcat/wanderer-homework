// Programmer Homework - by Michael "HELLCAT"

#include "FileIo.h"
#include <iostream>
#include <fstream>
#include "../Types/ErrorException.h"

using namespace std;

FileIo::FileIo()
{
    errorLogger = new Error("FileIo");
}

FileIo::~FileIo()
{
    delete errorLogger;
}

RouteDefinition* FileIo::ReadRouteDefinitionFromFile(std::string fileName)
{
    string readLine;
    ifstream routeDefinitionFile(fileName);
    int i;
    RouteDefinition* route;

    if (routeDefinitionFile.is_open())
    {
        getline(routeDefinitionFile, readLine);
        i = stoi(readLine);

        route = new RouteDefinition(i);

        try
        {
            if (!routeDefinitionFile.good())
            {
                throw ErrorException("Failed to read day count from route definition input file");
            }

            getline(routeDefinitionFile, readLine);
            route->SetDayCount(stoi(readLine));

            for (i = 0; i < route->GetStopCount(); i++)
            {
                if (!routeDefinitionFile.good())
                {
                    throw ErrorException("Failed to read distances for all stops from route definition input file");
                }

                getline(routeDefinitionFile, readLine);
                route->AddNextDistance(stoi(readLine));
            }
        }
        catch (ErrorException& exception)
        {
            errorLogger->LogError(exception.GetErrorMessage());
        }
    }
    else
    {
        errorLogger->LogError("Failed to read route definition input file");
        route = new RouteDefinition();
    }

    return route;
}
