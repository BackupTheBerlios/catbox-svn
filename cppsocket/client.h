#ifndef _CLIENT_H_
#define _CLIENT_H_
#include <iostream>
#include <sys/types.h>#include <sys/socket.h>
#include <netinet/in.h>#include <arpa/inet.h>
#include "constants.h"
#include "socket.h"
using namespace std;
class CClient
{
	class ClConn
	{
		public:
		char *addr;
		int c_socket;
		ClConn *next;
	};
private:
ClConn *clStart;
protected:
public:
char *addr;
CClient *clLocal;
CClient *clNew;
static bool ClientOccupied[MAX_CLIENTS];
int c_socket;
static int rang;
CClient();
~CClient();
void CClient::GetInfo();
bool CClient::AppendClient();
};
#endif