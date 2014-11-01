#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
#include "win.h"
#include <sys/time.h>
#include <time.h>
#include <cstdio>
#define MAX_EXT 12

using namespace std;

//////////////////////////////////////

void print(ostream &output, ofstream &file, const string dir, const string str)
{ 
	//fileName.open(file.c_str( ));
	if(file.is_open())
	{
		file << "Found : " << dir << "\\" << str << endl;
	}
	else
	{
		output << "Found : " << dir << "\\" << str << endl;
	}

}

///////////////////////////////////////

void getString(char search[], char var[2][20], int &ando)
{
    int flag=1;
    int i,j,k;

    for(i=0,j=0,k=0; search[i] != '\0'; i++)
    {
        if(search[i] == '|')
        {
            flag = 0;
        }
        else if(search[i] == '&')
        {
            flag = 0;
            ando=1;
        }
        else if(flag)
        {
            var[1][j] = search[i];
            j++;
        }
        else
        {
            var[2][k] = search[i];
            k++;
        }
    }

    var[1][j] = '\0' ;
    var[2][k] = '\0' ;


}

////////////////////////////////////////

void findFile(char search[2][20], ofstream &file,int dirs, int ando)  // Find file
{
    ifstream fileInput;
    int offset,c=0,flag;
    string line,di;
    char filetx[500];
    int nvar2=1;

    if(search[2][0] == '\0')
        nvar2=0;

    strcpy(filetx,"findTemp.txt");
    fileInput.open(filetx);

    if( ! fileInput ) 
    {
        cout << "File database is not created, create database by running \'Findfile -o\' " << endl;
        return;
    }

   
    while(!fileInput.eof()) 
    {   
        getline(fileInput, line);
        offset = line.find("$", 0);

        if(offset == 0)
        {
            getline(fileInput, line);
            di = line; // directory name
            flag = 1;
            continue; 
        }

        offset = line.find(search[1], 0);
        int offset1 = line.find(search[2], 0);
        if ( offset != string::npos && !dirs) 
        {
            if ( offset1 != string::npos && !dirs && ando) 
            {
                print(cout, file , di, line);
                c++;
                
            }
            else if(!ando)
            {
                print(cout, file , di, line);
                c++;
            }

        }
        else if ( offset1 != string::npos && !dirs && !ando && nvar2 ) 
        {
            print(cout, file , di, line);
            c++;
        }
        else if(dirs && flag)
        {
            offset = di.find(search[1], 0);
            if ( offset != string::npos)
            {
            	//line("");
                print(cout, file , di, line);
                c++;
                flag = 0;
            }

        }
    }

    fileInput.clear();
    fileInput.close();

    if(c==0)
        cout << "File doesn't exist \n";
    else
        cout << "There are " << c << " matches" << endl ;

}

///////////////////////////////

void findfileDir(char search[2][20],char dirc[], int ando)
{
    ifstream fileInput;
    int offset,c=0;
    string line;
    char filetx[500];
    int nvar2=1;
    int offset1;

    if(search[2][0] == '\0')
        nvar2=0;

    strcpy(filetx,"findTemp.txt");
    fileInput.open(filetx);

    if( ! fileInput ) 
    {
        cout << "File database is empty, create database by running \'Findfile -o\' " << endl;
        return;
    }
    int fl =1;
    while(!fileInput.eof() && fl)
    {
        getline(fileInput, line);
        offset = line.find("$", 0);

        if(offset == 0)
        {
            getline(fileInput, line);
            offset = line.find(dirc, 0);
            if ( offset != string::npos)
            {
            	cout << line << endl ;
                fl=0;
            }
       	}
    }

    if(fileInput.eof())
    {
        cout << "Invalid path !" << endl ;
        return;
    }

    int flag=1;
    while(!fileInput.eof() && flag) 
    {   
        getline(fileInput, line);
        offset = line.find("$", 0);

        if(offset == 0)
        {
            getline(fileInput, line);
            offset = line.find(dirc, 0);
            if ( offset == string::npos)
                flag=0;
        }
        else
        {

        offset = line.find(search[1], 0);
        offset1 = line.find(search[2], 0);
        if ( offset != string::npos) 
        {
            if ( offset1 != string::npos && ando) 
            {
                cout <<"Found : "<< dirc << "\\" << line << endl;
                c++;
                
            }
            else if(!ando)
            {
                cout <<"Found : "<< dirc << "\\" << line << endl;
                c++;
            }

        }
        if ( offset1 != string::npos && !ando && nvar2 ) 
        {
            cout <<"Found : "<< dirc << "\\" << line << endl;
            c++;
        }
        }

    }


    fileInput.clear();
    fileInput.close();

    if(c==0)
        cout << "File doesn't exist \n";
    else
        cout << "There are " << c << " matches" << endl ;
}

/////////////////////////////////////////
// start of main()

int main(int argc, char *argv[])
{
    char search[100],outfile[100],var[2][20];
	ofstream file,FileOut;
    TCHAR pwd[MAX_PATH];
    int dirs,ando=0;


    if(strcmpi(argv[1],"-db")==0) // -db :  create our database
    {
        if (!GetCurrentDirectory(MAX_PATH,pwd))
        {
            cout << "error ! cant find the path !\n";
            return errno;
        }
        file.open("findTemp.txt");
        cout << "Files and folders database of "<< pwd << " is creating..." << endl;
        file << "$" << endl << pwd << endl;

        clock_t tStart = clock();

        ListDirectoryContents(pwd,file);

        printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

        file.close();
        exit(0);
    }


    if(strcmpi(argv[1],"-f")==0) // -f : write output in specific file
    {

        strcpy(outfile,argv[2]);
        strcpy(search,argv[3]);
        cout << "File to be searched is : " << search <<" outfile : " << outfile << endl;
        // cout << outfile << search << endl ;
        dirs = 0;
        FileOut.open(outfile);
        getString(search,var,ando);
        findFile(var,FileOut,dirs,ando);
        exit(0);
    }
    else if(strcmpi(argv[1],"-d")==0) // -d : Find in specific folder
    {
        char dirc[100];
        strcpy(dirc,argv[2]);
        strcpy(search,argv[3]);
        cout << "File  to be searched is :" << search << " in directory : " << dirc << endl;
        getString(search,var,ando);
        findfileDir(var,dirc,ando);
        exit(0);
    }
    else
    {
        strcpy(search,argv[1]);
        //if(strcmpi(argv[1],"-d")==0)
        dirs = 0;
        cout << "File  to be searched is :" << search << endl;
        clock_t tStart = clock();
        getString(search,var,ando);
        findFile(var,FileOut,dirs,ando);
        printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    }

    return 0;
}