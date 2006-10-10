#include "ServerUnit.h"

ServerUnit::ServerUnit()
{
	cServerSocket = new CSocket();
	cout << "Created Socket."<<endl;
}

ServerUnit::~ServerUnit()
{
	delete cServerSocket;
	cout << "Deleted Socket."<<endl;
}
