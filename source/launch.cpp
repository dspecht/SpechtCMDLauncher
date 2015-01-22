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

internal int
CLConfigParser(char *configFile)
{
    FILE *cfg = fopen(configFile, "r");

    if (cfg)
    {
        //TODO: Look at doing this dynamicly so we don't possible run over
        char currentLine[256] = {};
        int validLineCount = 0;

        while(fgets(currentLine, 256, cfg))
        {
            ParsingApps[validLineCount] = SplitLineToAppPathPair((char *)&currentLine);
            validLineCount++;
        }

        fclose(cfg);
        return validLineCount;
    }
    else
    {
        printf_s("\nThe config file was not found, please check the name : %s", configFile);
        fclose(cfg);
        return 0;
    }
}

internal void
CLArgsParser(char *arg, int validAppCount)
{
    if(compareString(arg,"-h") || compareString(arg,"--help") || compareString(arg,"/?"))
    {
        printf_s("\nUSAGE: launch [--help] [-h] [/?] <alais to launch>");
        printf_s("\nPlease make sure the alais is in the config, it won't work if it is not");
        printf_s("\nConfig file should be formated such as | alias=\"<path to some executable>\"");
    }
    else
    {
        for(int index = 0; index < validAppCount; index++)
        {
            if(compareString(arg, ParsingApps[index].application))
            {
                //DEBUG printf_s("\nPATH -> %s\n", ParsingApps[i].path);
                char *buffer = CatString("start \"\" ", ParsingApps[index].path);
                system(buffer); //TODO: See what else we can use here
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc  > 1)
    {
        // this assumes the config.cfg is in the same directory as the exe. may look at changing this to relative  or soemthing?
        int validApplicationCount = CLConfigParser("./config.cfg");
        if(validApplicationCount > 0)
        {
            char *cmdArg = argv[1];
            CLArgsParser(cmdArg, validApplicationCount);
        }
        else
        {
            printf_s("\nConfig File Error, Either file is empty or formated wrong | use launch -h to get help on using this cli program");

        }
    }
    else
    {
        printf_s("\ninvalid argument count: must have 1 arg\n");
    }

    return 0;
}
