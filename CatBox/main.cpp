#include <iostream>
#include "ServerUnit.h"
#include "main.h"
int init (ServerUnit *SUE);
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
	return (0);
}

int init (ServerUnit *SUE)
{
//	SUE->cServerSocket->ServerAddress.si
	return (0);
}
