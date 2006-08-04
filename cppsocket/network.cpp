#include "network.h"
#include "socket.h"
using namespace std;
CNetwork::CNetwork()
{
	InstanceCount++;
	cout << "CNetwork Klasse erstellt, Nr: " << InstanceCount << "\n";
}
void CNetwork::Connect(const char* cHostname, int iPort)
{
}
CNetwork::~CNetwork()
{
	InstanceCount--;
	cout << "CNetwork Klasse zerstoert\n";
}