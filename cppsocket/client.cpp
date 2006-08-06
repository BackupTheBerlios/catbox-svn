#include "client.h"
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