#include <iostream>
#include <dirent.h>
#include "ServerUnit.h"
#include "ClientUnit.h"
#include "main.h"
int init (ServerUnit *SUE);
int checkForModules(const char *filename);
int main(int argc, char *argv[])
{ 
	int running=1;
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
			int MaxListeners = MAX_WAITING_LIST;
			ServerUnit *SUEnts[MAX_UNITS];
			SUEnts[0] = new ServerUnit();
			SUEnts[0]->cServerSocket->createSocket(1);
			SUEnts[0]->cServerSocket->startServer(CURPORT);
			SUEnts[0]->cServerSocket->startListening(MaxListeners);	
			//SUEnts[0]->cServerSocket->acceptClient();
			while(running)
			{
				SUEnts[0]->cServerSocket->acceptClient();
				cout << "Got a Connection from " << inet_ntoa(SUEnts[0]->cServerSocket->ClientAddress.sin_addr)<<endl;
			}
			SUEnts[0]->cServerSocket->stopServer();
			delete SUEnts[0];
			return (0);
		}
		else if(Temp == 2)
		{
			cout << "Using CatBox Client Mode..." << endl;
			checkForModules("plugins");
			ClientUnit *CUEnts[1];
			CUEnts[0] = new ClientUnit();
			CUEnts[0]->cClientSocket->createSocket(1);
			CUEnts[0]->cClientSocket->connectToServer("127.0.0.1",CURPORT);
			close(CUEnts[0]->cClientSocket->CurrentSocket);
			cout << "Closed connection. Quitting session now."<<endl;
		}
	}

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
		if(closedir(DirectoryPointer) == -1)
		{
			cout << "Couldn't close directory."<<endl;
		}
		
	}
		
	return(0);
}
