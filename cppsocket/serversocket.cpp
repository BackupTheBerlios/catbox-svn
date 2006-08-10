#include "serversocket.h"
#include "constants.h"
CServerSocket::CServerSocket(int iType) : CSocket(iType)
{
	int i;
	for(i=0;i<=MAX_CLIENTS;i++)
	s_clientsocket[i] = -1;	
}
CServerSockt::~CServerSocket()
{
}
