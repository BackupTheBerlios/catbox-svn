#include "ClientUnit.h"

ClientUnit::ClientUnit()
{
	cClientSocket = new CSocket();
	cout << "Created Client Unit."<<endl;
}

ClientUnit::~ClientUnit()
{
	delete cClientSocket;
	cout << "Deleted Client Unit." << endl;
}
