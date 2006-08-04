#ifndef _SOCKET_H_
#define _SOCKET_H_
#include <iostream>
#include <sys/types.h>#include <sys/socket.h>
#include <netinet/in.h>#include <arpa/inet.h>
using namespace std;
#define MAX_CLIENTS 10
#define MAX_SERVERBUFFER 2048
class CSocket
{
	private:
	static int InstanceCount;
	protected:
	int s_socket;
	int s_type;
	int s_flag;
	int s_clientsocket[MAX_CLIENTS]

	public:
	CSocket(int iType);
	~CSocket();
	void Socket();
	void Bind(int iPort);
	bool IsListening();
	void SetListen(int iClients);
};
#endif