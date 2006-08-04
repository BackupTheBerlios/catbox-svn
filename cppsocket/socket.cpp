#include "socket.h"

CSocket::CSocket(int iType)
{
	InstanceCount++;
	cout <<"CSocket Klasse erstellt, Nr.: " << InstanceCount <<"\n";
	s_socket = -1;
	s_type = iType;
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

void CSocket::Bind(int iPort)
{
	int iBinding;
	if(s_socket ==-1)cout<<"Konnte bind() nicht ausführen, es wurde kein Socket erzeugt\n";
	struct sockaddr_in addr;
	addr.sin_family = s_type;
	addr.sin_addr.s_addr= inet_addr("127.0.0.1"); // htonl(INADDR_ANY)
	addr.sin_port = htons(iPort);
	iBinding = bind(s_socket,(struct sockaddr*)&addr,sizeof(addr));
	if (iBinding < 0)cout << "Konnte Socket nicht an Port "<<iPort<<" binden, breche ab" <<endl;
}

bool CSocket::IsListening()
{
	if (s_flag < 1)
	{
		cout <<"Das Socket ist nicht im Listen-Modus\n";
		return(false);
	}
	else
	{
	cout <<"Das Socket ist bereits im Listen-Modus\n";
	return(true);
	} 
}
void CSocket::SetListen(int iClients)
{
	if(listen(s_socket,iClients) == -1)
	{
		cout << "Konnte nicht in den Listen-Modus wechseln\n";
	}
	s_flag = 1; // Starts listening
}