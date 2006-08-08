#include <iostream>
#include <cstdio>
#include "socket.h"
#include "network.h"
#include "client.h"
using namespace std;
int CSocket::InstanceCount = 0;
int CNetwork::InstanceCount = 0;
bool CClient::ClientOccupied[MAX_CLIENTS];
int main(int argc , char **argv)
{
	CNetwork cNet;
	CSocket cS(SOCK_STREAM);
	CClient cC;
	cout << argc;
	char *argument=argv[0]+2;
	cout << endl;
	cout << "Executable is named <<" << argument << ">> and uses the following arguments:"<< endl;

	for(int i=1;i<argc;i++)
	{
		char *arguments = argv[i];
		
		cout << arguments << "\n";
	}
	if (argc == 1)
	{	
		cout << "No Arguments delivered.\n";	
	}
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
			if(CClient::ClientOccupied[iCnt]== false)
			{
				CClient::ClientOccupied[iCnt] == true;
				cout <<"Freien Slot fuer Client gefunden, warte auf Verbindung.\n";
				cout << iCnt<<endl;
				CSocket cSClient = cS.AcceptClient();
				
			}
		}
		break;
	cS.ListClients();
		
	}
	/*for(;;)
	{
		cS.AcceptClient();
	}*/	
	return(0);
}