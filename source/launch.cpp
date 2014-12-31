// Launch.cpp is a command line utilitiy for launching Applications without
// a .bat script from a config file
// TODO: Write my own token parsing, and compare

#include <cstdio>
#include <stdlib.h>
#include "SpechtStringLib.cpp"

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

    char *tempStr = str;
    char *token = SplitString(tempStr, delim, path);

    //TODO: Make this less janky
    // This also assumes there is only 2 parts a application name and a
    // application path
    if(token)
    {
        //printf("\nDEBUG | Application -> %s\n", token);
        //printf("\nDEBUG | Path -> %s\n", path);

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
        printf("Thanks for using CMDLAUNCHER: to use this application you need to ensure");
        printf(" that you have a config.cfg file in the same location as the .exe this");
        printf(" file should be in the format of <nameToCallFromCMDLine>=<PathToExecutable>");
        printf("\nLaunch from the command line like launch <name> so 'launch vlc' could be");
        printf(" valid if there was a vlc=<somePath> in your config file");
    }
    else
    {
        for(int index = 0; index < validAppCount; index++)
        {
            if(compareString(arg, ParsingApps[index].application))
            {
                //printf("\nPATH -> %s\n", ParsingApps[i].path);

                char *buffer = CatString("call ", ParsingApps[index].path);
                //printf("output: %s\n",buffer);
                system(buffer); //TODO: See what else we can use here
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc  > 1)
    {
        int validApplicationCount = CLConfigParser("config.cfg");
        if(validApplicationCount > 0)
        {
            char *cmdArg = argv[1];
            CLArgsParser(cmdArg, validApplicationCount);
        }
    }
    else
    {
        printf("\ninvalid argument count: must have 1 arg\n");
    }

    return 0;
}
