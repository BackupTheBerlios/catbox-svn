#include "socket.h"

CSocket::CSocket(int iType)
{
	InstanceCount++;
	cout <<"CSocket Klasse erstellt, Nr.: " << InstanceCount <<"\n";
	s_socket = -1;
	s_type = iType;
	s_flag = 0;
}
CSocket::CSocket()
{
	InstanceCount++;
	cout <<"CSocket Klasse erstellt, Nr.: " << InstanceCount <<"\n";
	s_socket = -1;
	s_type = -1;
	s_flag = 0;
}
CSocket::~CSocket()
{
	InstanceCount--;
	cout << "CSocket Klasse zerstoert\n";
}
void CSocket::Socket()
{
	s_socket = socket(AF_INET, s_type, 0);
	if(s_socket == -1)cout<<"Fehler bei der Socket-Erzeugung\n";
	cout<<"Socket erfolgreich erzeugt\n";
	
}


