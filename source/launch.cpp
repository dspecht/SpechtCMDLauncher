// Launch.cpp is a command line utilitiy for launching Applications without
// a .bat script from a config file

#include <cstdio>
#include <stdlib.h>
#include "cStringLib.h"

#define internal static
#define local_persist static
#define global_variable static

global_variable int numberOfCLArgs = 0;

struct AppPathPair
{
    char *application;
    char *path;
};

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
SearchAndRun(char *arg[], char *fileName)
{
    FILE *configFile;
    char currentLine[512] = {};
    bool isFinished = false;
    AppPathPair app = {};

    if(!fopen_s(&configFile, fileName, "r"))
    {
        while(fgets(currentLine, 512, configFile))
        {
            app = SplitLineToAppPathPair((char *)&currentLine);

            if(compareString(app.application, arg[1]))
            {
                fclose(configFile);

                isFinished = true;

                //NOTE(dustin) if you use buffer please free it
                //char *buffer = CatString("start \"\" ", app.path);

                if(numberOfCLArgs > 2)
                {
                    int extraArgs = numberOfCLArgs - 2;
                    char *buffer = CatString(app.path, " ");

                    for(int i = 0; i <= extraArgs; i++)
                    {
                        buffer = CatString(buffer, arg[i+2]);
                        buffer = CatString(buffer, " ");
                    }
                    system(buffer);
                    free(buffer);
                }
                else
                {
                    system(app.path);
                }
                break;
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
    else
    {
        printf_s("Error with config File");
    }
}

int main(int argc, char *argv[])
{
    if (argc  > 1)
    {
        numberOfCLArgs = argc;
        //TODO: Look at not hard coding this so we can run it without rebuilding on other systems
        SearchAndRun(argv, "C:/Users/Spector/Scripts/config.cfg");
    }
    else
    {
        printf_s("\ninvalid argument count: must have 1 arg\n");
    }

    return 0;
}
