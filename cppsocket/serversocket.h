#ifndef _SERVERSOCKET_H_
#define _SERVERSOCKET_H_
#include <iostream>
#include <sys/types.h>
#include <netinet/in.h>
#include "socket.h"
using namespace std;
class CServerSocket : public CSocket
{
	public:
	CServerSocket(int iType);
	~CServerSocket();
};
#endif