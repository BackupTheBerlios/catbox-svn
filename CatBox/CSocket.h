#ifndef CSOCKET_H_
#define CSOCKET_H_
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "main.h"
using namespace std;
class CSocket
{
protected:
	int CurrentSocket;
	int ConnectionSocket;

public:
	socklen_t AddressLength;
	struct sockaddr_in ServerAddress;
	struct sockaddr_in ClientAddress;
	CSocket();
	virtual ~CSocket();
	int getSocket();
	int setSocket(int Socket);
	int createSocket(int type);
	int destroySocket();
	int startServer(int port);
	int stopServer();
	int startListening(int lengthOfQueue);
	int acceptClient();
	bool isSocketCreated();
};

#endif /*CSOCKET_H_*/
