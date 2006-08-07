#include "client.h"
#include "socket.h"
#include "constants.h"
int CClient::rang=0;
CClient::CClient()
{
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
