#include "client.h"
#include "socket.h"
#include "constants.h"
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
void CClient::ListClients()
{
	rang++;
	cout << "Client Nr. " << rang << " hat die IP: "; //<< 	addr << "\n";
}