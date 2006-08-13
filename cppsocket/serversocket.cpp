#include "serversocket.h"
#include "clientsocket.h"
#include "socket.h"
#include "constants.h"
CServerSocket::CServerSocket(int iType) : CSocket(iType)
{
	int i;
	for(i=0;i<=MAX_CLIENTS;i++)
	s_clientsocket[i] = -1;	
}
CServerSocket::~CServerSocket()
{
}
void CServerSocket::Bind(int iPort)
{
	int iBinding;
	if(s_socket ==-1)cout<<"Konnte bind() nicht ausführen, es wurde kein Socket erzeugt\n";
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(struct sockaddr_in));
	addr.sin_family = s_type;
	addr.sin_addr.s_addr= htonl(INADDR_ANY);
	addr.sin_port = htons(iPort);
	iBinding = bind(s_socket,(struct sockaddr*)&addr,sizeof(addr));
	if (iBinding < 0)
	{
		cout << "Konnte Socket nicht an Port "<<iPort<<" binden, breche ab"<<endl;
		exit(1);
	}
	else
	{
		cout << "Socket an Port " << iPort <<" gebunden!\n";
	}
}

void CServerSocket::SetListen(int iClients)
{
	if(listen(s_socket,iClients) == -1)
	{
		cout << "Konnte nicht in den Listen-Modus wechseln\n";
	}
	else
	{
		cout << "Started listening..." << endl;
	}
	s_flag = 1; // Starts listening
}

bool CServerSocket::IsListening()
{
	if (s_flag == 0)
	{
		cout <<"Das Socket ist nicht im Listen-Modus\n";
		return(false);
	}
	if (s_flag == 1)
	{
		cout <<"Das Socket ist bereits im Listen-Modus"<<endl;
		return(true);
	} 
	else
	{
		cout << "No idea.. I guess it failed.\n";
		return (false);
	}
}

void CServerSocket::ListClients()
{
	for(int i=0;i<=MAX_CLIENTS;i++)
	{
		if(CClientSocket::ClientOccupied[i] != -1)
		cout << "Client Nr. " << i+1 << " hat die IP: "; // << cC[i]->addr << "\n";
	}
}

void CServerSocket::AcceptClient()
{ 
	int errcheck;
	int i;
	int correctid;
	   for (i=0; i<MAX_CLIENTS; i++)
      s_clientsocket[i] = -1;
	FD_ZERO(&c_sockets);
	FD_SET(s_socket,&c_sockets);
	for(i=0;i<MAX_CLIENTS;i++)
	{
		if(s_clientsocket[i] != -1)
		{
			FD_SET(s_clientsocket[i],&c_sockets);
		}	
	}
	if(select(FD_SETSIZE,&c_sockets,NULL,NULL,NULL) < 0)
	cout <<"Select failed"<<endl;
	if(FD_ISSET(s_socket,&c_sockets))
	{
		for(correctid=0;correctid<MAX_CLIENTS;correctid++)	
		{
			if(s_clientsocket[correctid] == -1)
			{
				s_clientsocket[correctid] = accept (s_socket, &s_client[correctid],&client_len);
				if (s_clientsocket[correctid] == -1) cout <<"Error accepting client!"<<endl;
				
			//    cC->addr = inet_ntoa(s_client[i].sin_addr);i	
				
				//	cout << "Man abord: " << cC.addr  <<endl;
				break;
			}
		}
	}
	/*
	for(i=0;i<MAX_CLIENTS;i++)
	{
		if(s_clientsocket[i] != -1 && FD_ISSET(s_clientsocket[i],&c_sockets))
		{
			errcheck = recv(s_clientsocket[i],recv_buffer,MAX_SERVERBUFFER,0);
			if(errcheck <= 0)
			{
				close(s_clientsocket[i]);
				s_clientsocket[i] = -1;
				cout << "Connection lost!"<<endl;
			}
		}
	}*/ 
}