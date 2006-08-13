#include "clientsocket.h"
#include "constants.h"
#include "socket.h"

//int CClient::rang=0;

CClientSocket::CClientSocket() : CSocket(SOCK_STREAM)
{
	clNew=NULL;
	clLocal=NULL;
	for(int c=0;c<=MAX_CLIENTS;c++)
	{
		ClientOccupied[c] = 0;
	}
	cout << "New Client created.\n";
}
CClientSocket::~CClientSocket()
{
	cout << "Client destroyed.\n";
}
void CClientSocket::GetInfo()
{
}
bool CClientSocket::AppendClient()
{
	CClientSocket *a,*b;
	if(clNew == NULL)
	{
	clLocal = new CClientSocket;
	
//	inet_aton("31.121.11.11",(struct sockaddr*)&CSocket::s_client[0].sin_addr);
	//clLocal->addr = inet_ntoa(CSocket::s_client[0].sin_addr);
	}
	return(0);
}