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

bool bIsLocal(CatSocket *csSocket)
{
	switch(csSocket->bLocal)
	{
		case true:
		return true;
		case false:
		return false;
	} 
}
	
int iInitNetwork(CatSocket *csSocket)
{
	csSocket->sIsLocal = bIsLocal;
	csSocket->sConnect = socket;
	return (1);
}

int iSetUpSocket(CatSocket *csSocket, int iLocal, int iType)
{
	printf("iLocal = %d\n", iLocal);
	printf("iType = %d\n", iType);
	if(iLocal < 3 && iLocal > 0)
	{
		printf("iLocal = %d\n", iLocal);
		if(iLocal == 1) printf("Loopback device is being used.\n");
		if(iLocal == 2) printf("Standard-Ethernet device is being used.\n");
	}
		if(iType == 1)
	{
		csSocket->sConnect(iLocal, iLocal, SOCK_STREAM);
	}
	else if(iType == 2)
	{
		csSocket->sConnect(iLocal, iLocal, SOCK_DGRAM);
	}
	else
	{
		printf("%d is no valid type",iLocal);
	}
}
