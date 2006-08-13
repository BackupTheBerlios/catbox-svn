#ifndef _SOCKET_H_
#define _SOCKET_H_
#include <iostream>
#include <sys/types.h>#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <string.h>//#include "clientsocket.h"
#include "socket.h"
#include "constants.h"
using namespace std;
class CSocket
{
	private:
	int omg;
	public:
	static int InstanceCount;
	char recv_buffer[MAX_SERVERBUFFER];
	int s_socket;
	int s_type;
	int s_flag;
	
	socklen_t client_len;
	CSocket(int iType);
	CSocket();
	~CSocket();
	void Socket();

};
#endif