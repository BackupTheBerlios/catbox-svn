#include "ServerUnit.h"

ServerUnit::ServerUnit()
{
	cServerSocket = new CSocket();
	cout << "Created Server Unit."<<endl;
}

ServerUnit::~ServerUnit()
{
	delete cServerSocket;
	cout << "Deleted Server Unit."<<endl;
}
