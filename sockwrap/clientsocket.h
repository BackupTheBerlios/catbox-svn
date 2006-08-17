#ifndef _CLIENTSOCKET_H_
#define _CLIENTSOCKET_H_
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "socket.h"
#include "constants.h"
using namespace std;
class CClientSocket : public CSocket
{
public:
CClientSocket *clLocal;
CClientSocket *clNew;
static bool ClientOccupied[MAX_CLIENTS];
int c_socket;
static int rang;
CClientSocket();
CClientSocket(int iType);
~CClientSocket();
void GetInfo();
bool AppendClient();
};
#endif