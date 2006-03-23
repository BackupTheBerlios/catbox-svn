#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "daemon.h"
/*!
@brief This is the linux-daemon for CatBox
@author Michael Durrer
@version 0.1
@date 20.03.2006
@bug No bugs known(,yet :)
@param 
@return
*/

int iIsLocal(CatSocket *csSocket)
{
	switch(csSocket->iLocal)
	{
		case 1:
		return 1;
		case 0:
		return 0;
	} 
}
	
int iInitNetwork(CatSocket *csSocket)
{
	csSocket->sIsLocal = iIsLocal;
	csSocket->sConnect = socket;
	return (1);
}

int iSetUpSocket(CatSocket *csSocket, int iLocal, int iType)
{
	printf("iLocal = %d\n", iLocal);
	printf("iType = %d\n", iType);
	if(iLocal < 3 && iLocal > 0)
	{
		if(iLocal == 1) printf("Loopback device is being used.\n");
		if(iLocal == 2) printf("Standard-Ethernet device is being used.\n");
	}
	if(iType == 1)
	{
		csSocket->socket = csSocket->sConnect(iLocal, iType, SOCK_STREAM);
	}
	else if(iType == 2)
	{
		csSocket->socket = csSocket->sConnect(iLocal, iType, SOCK_DGRAM);
	}
	else
	{
		printf("%d is no valid type",iLocal);
	}
	if (csSocket->socket < 0) printf("Socket creation failed with error-code %d",csSocket->socket);
}
