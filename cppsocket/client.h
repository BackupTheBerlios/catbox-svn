#ifndef _CLIENT_H_
#define _CLIENT_H_
#include <iostream>
#include <sys/types.h>#include <sys/socket.h>
#include "constants.h"
using namespace std;
class CClient
{
private:
protected:
public:
char *addr;
static bool ClientOccupied[MAX_CLIENTS];
int c_socket;
static int rang;
CClient();
~CClient();
void CClient::GetInfo();
};
#endif