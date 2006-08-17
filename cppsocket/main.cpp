#include <iostream>
#include <cstdio>
#include "socket.h"
#include "network.h"
#include "serversocket.h"
#include "clientsocket.h"
using namespace std;
int CSocket::InstanceCount = 0;
int CNetwork::InstanceCount = 0;
bool CClientSocket::ClientOccupied[MAX_CLIENTS];
int main(int argc , char **argv)
{

	CNetwork cNet;
	CServerSocket cS(SOCK_STREAM);
	CClientSocket cC;
	cout << argc;
	char *argument=argv[0]+2;
	cout << endl;
	cout << "Executable is named <<" << argument << ">> and uses the following arguments:"<< endl;
	if (argc == 1)
	{	
		cout << "No Arguments delivered.\n";	
		exit(1);
	}
	for(int i=1;i<argc;i++)
	{
		char *arguments = argv[i];
		
		cout << arguments << "\n";
	}
	switch(atoi(argv[1])
	{
		case SERVER_MODE:
	cNet.iNet=20;
	cS.Socket();
	cS.Bind(1050);
	cS.IsListening();
	cS.SetListen(2);
	cS.IsListening();
	while(1)
	{
		for(int iCnt=0;iCnt <= 1;iCnt++)
		{
			if(CClientSocket::ClientOccupied[iCnt]== false)
			{
				CClientSocket::ClientOccupied[iCnt] == true;
				cout <<"Freien Slot fuer Client gefunden, warte auf Verbindung.\n";
				cout << iCnt<<endl;
				cS.AcceptClient();
				
			}
		}
		break;
	cS.ListClients();
		
	}
	break;
		case CLIENT_MODE:
		cout << "You've chosen the client-mode. Now you'll die :(\n";
	}
	/*for(;;)
	{
		cS.AcceptClient();
	}*/	
	return(0);
}