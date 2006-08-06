#ifndef _SOCKET_H_
#define _SOCKET_H_
#include <iostream>
#include <sys/types.h>#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <string.h>
#include <unistd.h>#include <arpa/inet.h>
#include "client.h"
#define MAX_CLIENTS 10
#define MAX_SERVERBUFFER 2048
using namespace std;
class CSocket
{
	private:
	static int InstanceCount;
	protected:
	char recv_buffer[MAX_SERVERBUFFER];
	int s_socket;
	int s_type;
	int s_flag;
	fd_set c_sockets;
	int s_clientsocket[MAX_CLIENTS];
	struct sockaddr_in s_client[MAX_CLIENTS];
	socklen_t client_len;
	
	public:
	CSocket(int iType);
	~CSocket();
	void Socket();
	void Bind(int iPort);
	bool IsListening();
	void SetListen(int iClients);
	void AcceptClient(CClient *cC);
};
#endif