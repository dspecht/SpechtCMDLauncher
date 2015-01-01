// This file is for a basic string library so I do not have to use <cstring>

int getStringLength(char *str)
{
    int result= 0;

    for(int index = 0; str[index]; index++)
    {
        ++result;
    }
    return result;
}

// Utliity function
void clearTempStringsToNull(char *str)
{
    for(int index = 0; str[index] ; index++)
    {
        str[index] = 0;
    }
}

//TODO: make another compreString that is case insensitive
//TODO: Mabye look at returning a value rather then hard 0 or 1
int compareString(char *fString, char *sString) // first/second String
{
    int firstStringLength = getStringLength(fString);

    if(firstStringLength != getStringLength(sString))
    {
        return 0;
    }
    for(int index = 0; index <= firstStringLength; index++)
    {
        if(fString[index] != sString[index])
        { return 0; }
    }
    return 1;
}

//NOTE(Dustin): You will have to free this memory if you use this function
char* CopyString(char *strToCopy)
{
    char *result = (char*)calloc(getStringLength(strToCopy)+1, sizeof(char));

    for (int index = 0; strToCopy[index]; index++)
    {
        result[index] = strToCopy[index];
    }
    return result;
}

//NOTE(Dustin): Overloaded function, the calle defines were the copy gets placed
void CopyString(char *strToCopy, char *placeToPutCopiedString)
{
    for (int index = 0; strToCopy[index]; index++)
    {
        placeToPutCopiedString[index] = strToCopy[index];
    }
}

//NOTE(Dustin): Enduser needs to free the resultstring
char* CatString(char *originString, char *strToCat)
{
    int originLength = getStringLength(originString);
    int catStrLength = getStringLength(strToCat);
    int outstringLength = (originLength + catStrLength);
    int catStrIndex = 0;

    char *result = ((char*)calloc(outstringLength+1, sizeof(char)));

    for(int index = 0; index < outstringLength; index++)
    {
        if(index < originLength)
        {
            result[index] = originString[index];
        }
        else
        {
            result[index] = strToCat[catStrIndex];
            catStrIndex++;
        }
    }
    return result;
}

//Overloaded function to let calle tell where to put the result
void CatString(char *originString, char *strToCat, char *outputString)
{
    int originLength = getStringLength(originString);
    int catStrLength = getStringLength(strToCat);
    int outstringLength = (originLength + catStrLength);
    int catStrIndex = 0;

    for(int index = 0; index < outstringLength; index++)
    {
        if(index < originLength)
        {
            outputString[index] = originString[index];
        }
        else
        {
            outputString[index] =strToCat[catStrIndex];
            catStrLength++;
        }
    }
}

// if no outputstring then calle has to free
char* SplitString(char *inputString, char strDelim, char *savePlace, char *outputString=NULL)
{
    bool isParsingStringToDelim = true;
    int index = 0;
    int resultIndex = 0;

    if(inputString) // see if null so we know to use the savePlace as the start
    {
        while (isParsingStringToDelim)
        {
            //TODO: make this take multiple possible delim characters
            if(inputString[index] == strDelim)
            {
                clearTempStringsToNull(savePlace);
                isParsingStringToDelim = false;
                index++;

                for(int localIndex = 0; inputString[index]; localIndex++)
                {
                    savePlace[localIndex] = inputString[index];
                    index++;
                }
            }
            else
            {
                if (inputString[index])
                {
                    resultIndex++;
                    index++;
                }
                else
                {
                    break;
                }
            }
        }

        if(resultIndex)
        {
            if(!outputString)
            {
                char *result = ((char*)calloc(resultIndex+1, sizeof(char)));

                for(int localIndex = 0; localIndex < resultIndex; localIndex++)
                {
                    result[localIndex] = inputString[localIndex];
                }

                return result;
            }
            else
            {
                for(int localIndex = 0; localIndex < resultIndex; localIndex++)
                {
                    outputString[localIndex] = inputString[localIndex];
                }
                return ""; // make sure if this is in a if that it doesnt fail all the time
            }
        }
    }

    return NULL;
}
