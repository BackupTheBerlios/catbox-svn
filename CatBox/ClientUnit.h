#ifndef CLIENTUNIT_H_
#define CLIENTUNIT_H_
#include <iostream>
#include "CSocket.h"
using namespace std;
class ClientUnit
{
protected:

public:
	ClientUnit();
	virtual ~ClientUnit();
	CSocket *cClientSocket;

};

#endif /*CLIENTUNIT_H_*/
