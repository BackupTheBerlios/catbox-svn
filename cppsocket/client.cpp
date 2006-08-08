#include "client.h"
#include "socket.h"
#include "constants.h"
int CClient::rang=0;
CClient::CClient()
{
	clStart=NULL;
	for(int c=0;c<=MAX_CLIENTS;c++)
	{
		ClientOccupied[c] = 0;
	}
	cout << "New Client created.\n";
}
CClient::~CClient()
{
	cout << "Client destroyed.\n";
}
void CClient::GetInfo()
{
}
bool CClient::AppendClient()
{
	ClConn *a,*b;
	if(clStart == NULL)
	{
	clStart = new ClConn;
	struct sockaddr_in bla;
	inet_aton("12.12.12.12",&bla.sin_addr);
	clStart->addr = inet_ntoa(bla.sin_addr);
	}
}