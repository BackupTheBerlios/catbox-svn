#include <iostream>
#include <dirent.h>
#include "ServerUnit.h"
#include "main.h"
int init (ServerUnit *SUE);
int checkForModules(const char *filename);
int main(int argc, char *argv[])
{ 
	if(argc < 2)
	{
		cout << "Please decide to use Server or Client mode like this:"<<endl;
		cout << "Server Mode: ./CatBox 1 <Port>" << endl << "Client Mode: ./CatBox 2 <IP> <Port>"<<endl;
		cout << "If no port is given, CatBox will use the standard port ( " << CURPORT << " )."<<endl;
		exit(1);
	}
	else
	{
		int Temp;
		Temp = atoi(argv[1]);
		if(Temp == 1)
		{
			cout << "Using CatBox Server Mode..." << endl;
			checkForModules("plugins");
		}
		else if(Temp == 2)
		{
			cout << "Using CatBox Client Mode..." << endl;
		}
	}
	int MaxListeners = MAX_WAITING_LIST;
	ServerUnit *SUEnts[MAX_UNITS];
	SUEnts[0] = new ServerUnit();
	SUEnts[0]->cServerSocket->createSocket(1);
	SUEnts[0]->cServerSocket->startServer(CURPORT);
	SUEnts[0]->cServerSocket->startListening(MaxListeners);
	SUEnts[0]->cServerSocket->stopServer();
//	init(SUEnts[0]);	
	delete SUEnts[0];
	return (0);
}

int init (ServerUnit *SUE)
{
//	SUE->cServerSocket->ServerAddress.si
	return (0);
}
int checkForModules(const char *filename)
{
	DIR *DirectoryPointer;
	struct dirent *DirectoryContent;
	int DirectoryCount;
	DirectoryPointer = opendir(filename);
	if(DirectoryPointer== NULL)
	{
		cout << "Couldn't find the Plugins directory, no plugins loaded. You can load them afterward manually on the console." << endl;
	}
	else
	{
		for(DirectoryCount=3;DirectoryCount!=0;DirectoryCount--)
		{
			DirectoryContent = readdir(DirectoryPointer);
		}
		while(DirectoryContent != NULL)
		{
			cout << "Loaded " << DirectoryContent->d_name << " plugin." <<endl;
			DirectoryContent = readdir(DirectoryPointer);
		}
		if(DirectoryCount <= 2)
		{
			cout << "No plugins found." << endl;
		}
		else
		{
			cout << "Loaded " << DirectoryCount << " plugins." << endl;
		}
	}
		
	return(0);
}
