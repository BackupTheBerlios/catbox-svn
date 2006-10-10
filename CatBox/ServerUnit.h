#ifndef SERVERUNIT_H_
#define SERVERUNIT_H_
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include "CSocket.h"
using namespace std;
class ServerUnit
{
protected:

public:
	CSocket *cServerSocket;
	ServerUnit();
	virtual ~ServerUnit();
};

#endif /*SERVERUNIT_H_*/
