#ifndef _CLIENTSOCKET_H_
#define _CLIENTSOCKET_H_
#include <iostream>
#include <sys/types.h>
#include <netinet/in.h>
#include "socket.h"
using namespace std;
class CClientSocket : public CSocket
{
	public:
	CClientSocket();
	CClientSocket(int iType);
	~CClientSocket();
};
#endif