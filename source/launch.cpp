// Launch.cpp is a command line utilitiy for launching Applications without
// a .bat script from a config file

#include <cstdio>
#include <stdlib.h>
#include "cStringLib.h"

#define internal static
#define local_persist static
#define global_variable static

struct AppPathPair
{
    char *application;
    char *path;
};

// TODO: Dynamicly store these so we don't have a hard limit and so we don't
// have to many
global_variable AppPathPair ParsingApps[100] = {};

internal AppPathPair
SplitLineToAppPathPair(char *str, char delim = '=')
{
    AppPathPair curProccessingApp = {};

    char *path= ((char*)calloc(getStringLength(str)+1, sizeof(char)));
    char *token = SplitString(str, delim, path);

    if(token)
    {
        //DEBUG PRINTS
        //printf_s("\nDEBUG | Application -> %s\n", token);
        //printf_s("\nDEBUG | Path -> %s\n", path);

        curProccessingApp.application = CopyString(token);
        curProccessingApp.path = CopyString(path);
    }
    else
    {
        printf_s("\nInvalid Token: %s\n", token);
    }

    free(token);
    free(path);

    return curProccessingApp;
}

internal void
SearchAndRun(char *arg, char *fileName)
{
    FILE *configFile;
    fopen_s(&configFile, fileName, "r");
    char currentLine[256] = {};
    bool isFinished = false;

    AppPathPair app = {};

    while(fgets(currentLine, 265, configFile))
    {
        app = SplitLineToAppPathPair((char *)&currentLine);

        if(compareString(app.application, arg))
        {
            fclose(configFile);

            isFinished = true;

            char *buffer = CatString("start \"\" ", app.path);
            system(buffer);
        }
        else
        {
            app = {};
        }
    }
    if(!isFinished)
    {
       fclose(configFile);
       printf_s("Unable to find %s as a valid command", arg);
    }
}

int main(int argc, char *argv[])
{
    if (argc  > 1)
    {
        SearchAndRun(argv[1], "./config.cfg");
    }
    else
    {
        printf_s("\ninvalid argument count: must have 1 arg\n");
    }

    return 0;
}
