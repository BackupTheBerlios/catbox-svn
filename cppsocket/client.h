#ifndef _CLIENT_H_
#define _CLIENT_H_
#include <iostream>
#include <sys/types.h>#include <sys/socket.h>
using namespace std;
class CClient
{
private:
protected:
public:
int c_socket;
CClient();
~CClient();
};
#endif