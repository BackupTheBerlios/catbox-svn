#include "clientsocket.h"
#include "constants.h"
CClientSocket::CClientSocket() : CSocket(SOCK_STREAM)
{
}
CClientSocket::CClientSocket(int iType) : CSocket(iType)
{
	
}
CClientSocket::~CClientSocket()
{
}
