#ifndef _SOCKET_H_
#define _SOCKET_H_
#include <iostream>
#include <sys/types.h>#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <string.h>#include "client.h"
#include "socket.h"
#include "constants.h"
using namespace std;
class CSocket
{
	private:
	int omg;
	static int InstanceCount;
	public:
	struct sockaddr s_client[MAX_CLIENTS];
	char recv_buffer[MAX_SERVERBUFFER];
	int s_socket;
	int s_type;
	int s_flag;
	fd_set c_sockets;
	int s_clientsocket[MAX_CLIENTS];	
	socklen_t client_len;
	CSocket(int iType);
	CSocket();
	~CSocket();
	void Socket();
	void Bind(int iPort);
	bool IsListening();
	void SetListen(int iClients);
	CSocket AcceptClient();
	void ListClients();
};
#endif