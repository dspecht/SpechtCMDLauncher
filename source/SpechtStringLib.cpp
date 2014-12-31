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

// Utliity function NOTE: Not currently used
void clearTempStringsToNull(char *str)
{
    int length = getStringLength(str);
    for(int i = 0; i < length; i++)
    {
        str[i] = 0;
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

//IF successful, calle has to free the result
char* SplitString(char *inputString, char strDelim, char *savePlace)
{
    char *tempParsingString = ((char*)calloc(getStringLength(inputString)+1, sizeof(char)));
    bool isParsingStringToDelim = true;
    int index = 0;
    int resultIndex = 0;

    if(inputString) // see if null so we know to use the savePlace as the start
    {
        CopyString(inputString, tempParsingString);
        clearTempStringsToNull(savePlace);
    }
    else
    {
        CopyString(savePlace, tempParsingString);
    }

    while (isParsingStringToDelim)
    {
        //TODO: make this take multiple possible delim characters
        if(tempParsingString[index] == strDelim)
        {
            isParsingStringToDelim = false;
            index++;

            for(int localIndex = 0; tempParsingString[(index)]; localIndex++)
            {
                savePlace[localIndex] = tempParsingString[index];
                index++;
            }
        }
        else if(tempParsingString[index])
        {
            resultIndex++;
            index++;
        }
    }

    if(resultIndex)
    {
        char *result = ((char*)calloc(resultIndex+1, sizeof(char)));

        for(int localIndex = 0; localIndex < resultIndex; localIndex++)
        {
            result[localIndex] = tempParsingString[localIndex];
        }

        free(tempParsingString);
        return result;
    }
    else
    {
        free(tempParsingString);
        return NULL;
    }
}

//Overloaded function allows calle to tell us were to put the result
void SplitString(char *inputString, char *outputString ,char strDelim, char *savePlace)
{
    char *tempParsingString = ((char*)calloc(getStringLength(inputString)+1, sizeof(char)));
    bool isParsingStringToDelim = true;
    int index = 0;
    int resultIndex = 0;

    if(inputString)
    {
        CopyString(inputString, tempParsingString);
    }
    else
    {
        CopyString(savePlace, tempParsingString);
    }

    while (isParsingStringToDelim)
    {
        //TODO: make this take multiple possible delim characters
        if(tempParsingString[index] == strDelim)
        {
            isParsingStringToDelim = false;
            index++;

            for(int localIndex = 0; tempParsingString[(index)]; localIndex++)
            {
                savePlace[localIndex] = tempParsingString[index];
                index++;
            }
        }
        else if(tempParsingString[index])
        {
            resultIndex++;
            index++;
        }
    }

    if(resultIndex)
    {

        for(int localIndex = 0; localIndex < resultIndex; localIndex++)
        {
            outputString[localIndex] = tempParsingString[localIndex];
        }

        free(tempParsingString);
    }
    else
    {
        free(tempParsingString);
    }
}
