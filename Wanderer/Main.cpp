// Programmer Homework - by Michael "HELLCAT"

#include "Functions/FileIo.h"
#include "Functions/Router.h"
#include <string>

int main(int argc, char* argv[])
{
    FileIo* fileIo;
    Router* router;
    int* distances;
    int maxDistance;
    int i;
    std::string fileName;

    if( argc > 1 )
    {
        fileName = argv[1];
    }
    else
    {
        printf("Benutze standard Datei 'route.txt', andere Dateien können per Parameter angegeben werden\n\n");
        fileName = "route.txt";
    }

    fileIo = new FileIo();
    router = new Router();

    RouteDefinition* route = fileIo->ReadRouteDefinitionFromFile(fileName);
    router->FindBestRoute(route, distances, maxDistance);

    // output our findings
    for (i = 0; i < route->GetDayCount(); i++)
    {
        printf("%2d. Tag: %3d km\n", i + 1, distances[i]);
    }
    printf("\nMaximum: %d km\n", maxDistance);

    return 0;
}
