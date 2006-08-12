#ifndef _SERVERSOCKET_H_
#define _SERVERSOCKET_H_
#include <iostream>
#include <sys/types.h>#include <sys/socket.h>
#include <netinet/in.h>#include <arpa/inet.h>
#include "socket.h"
using namespace std;
class CServerSocket : public CSocket
{
	public:
	CServerSocket(int iType);
	~CServerSocket();
	void Bind(int iPort);
	bool IsListening();
	void SetListen(int iClients);
	void AcceptClient();
	void ListClients();
};
#endif