d#include <iostream>
#include "ServerUnit.h"
#include "main.h"
int init (ServerUnit *SUE);
int main(int argc, char *argv[])
{ 
	ServerUnit *SUEnts[MAX_UNITS];
	SUEnts[0] = new ServerUnit();
	SUEnts[0]->cServerSocket->createSocket();
	SUEnts[0]->cServerSocket->startServer(CURPORT);
	SUEnts[0]->cServerSocket->stopServer();
//	init(SUEnts[0]);	
	return (0);
}

int init (ServerUnit *SUE)
{
//	SUE->cServerSocket->ServerAddress.si
	return (0);
}
