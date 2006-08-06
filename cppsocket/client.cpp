#include "client.h"
#include "socket.h"
#include "constants.h"
CClient::CClient()
{
	for(int c=0;c<=MAX_CLIENTS;c++)
	{
		ClientOccupied[c] = false;
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
	int c=1,d=0;
		do
		{
		if(ClientOccupied[d] == true)
		{
			cout << "Client Nr. " << c << " hat die IP: " << addr << "\n";
			c++;
		}
		d++;
		}while(d <= MAX_CLIENTS);
	
}