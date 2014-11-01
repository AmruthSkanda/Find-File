#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <sys/time.h>

using namespace std;

void ListDirectoryContents(const char *sDir,ofstream &file)
{
    WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;
    string str("");
    char sPath[400];

    //Specify a file mask. *.* = find everything!
    sprintf(sPath, "%s\\*.*", sDir);
    if((hFind = FindFirstFileEx (sPath, FindExInfoStandard, &fdFile, FindExSearchNameMatch, NULL, 0)) == INVALID_HANDLE_VALUE)
    {
        printf("Path not found: [%s]\n", sDir);
        return;
    }

    do
    {
        //Findfirstfile() will always return "." and ".." as the first two directories.
        if(strcmp(fdFile.cFileName, ".") != 0 && strcmp(fdFile.cFileName, "..") != 0)
        {
            sprintf(sPath, "%s\\%s", sDir, fdFile.cFileName);

            if(fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY);          
            else if(strcmp(fdFile.cFileName,"find_tmp.txt")!=0) // dont include find_temp.txt in database
                    file << fdFile.cFileName << endl;
            
        }
    }
    while(FindNextFile(hFind, &fdFile)); //Find the next file.


    sprintf(sPath, "%s\\*.*", sDir);
    if((hFind = FindFirstFileEx (sPath, FindExInfoStandard, &fdFile, FindExSearchNameMatch, NULL, 0)) == INVALID_HANDLE_VALUE)
    {
        return;
    }
    do
    {
        if(strcmp(fdFile.cFileName, ".") != 0 && strcmp(fdFile.cFileName, "..") != 0)
        {
            sprintf(sPath, "%s\\%s", sDir, fdFile.cFileName);
            //strlen(s)
            if(strlen(sPath))
            if(fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
            {               
                file << "$" << endl << sPath << endl;
                ListDirectoryContents(sPath,file); //Recursion
            }
        }
    }
    while(FindNextFile(hFind, &fdFile)); //Find the next file.
    
    FindClose(hFind); 
}