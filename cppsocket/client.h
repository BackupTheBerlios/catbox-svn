#ifndef _CLIENT_H_
#define _CLIENT_H_
#include <iostream>
#include <sys/types.h>#include <sys/socket.h>
#include <netinet/in.h>#include <arpa/inet.h>
#include "constants.h"
#include "socket.h"
using namespace std;
class CClientSocket
{

private:
protected:
public:
CClientSocket *clLocal;
CClientSocket *clNew;
static bool ClientOccupied[MAX_CLIENTS];
int c_socket;
static int rang;
CClientSocket();
~CClientSocket();
void CClientSocket::GetInfo();
bool CClientSocket::AppendClient();
};

#endif