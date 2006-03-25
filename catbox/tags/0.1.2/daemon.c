#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h> 
#include <netdb.h>
#include <string.h>
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
struct sockaddr_in client;
int sock2;
socklen_t len;
struct sockaddr_in server;
int iIsLocal(CatSocket *csSocket)
{
	int iRet;
	switch(csSocket->iLocal)
	{
		case 1:
		iRet = 1;
		break;
		case 0:
		iRet = 0;
		break;
	} 
	return(iRet);
}
	
int iInitNetwork(CatSocket *csSocket)
{
	csSocket->sIsLocal = iIsLocal;
	csSocket->sConnect = socket;
	return (1);
}

int iSetUpSocket(CatSocket *csSocket, int iLocal, int iType)
{
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
	memset(&server,0,sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl( INADDR_ANY );
	server.sin_port = htons( 666 );
	if(bind(csSocket->socket,(struct sockaddr*)&server,sizeof (server)) < 0) printf("Fehler beim Binden des Sockets!\n");
	if(listen(csSocket->socket,5) == -1)printf("Fehler beim Einrichten von Listen!\n!");
	return (1);
}

int iPollConnection(CatSocket *csSocket)
{
	
	len = sizeof( client );
        sock2 = accept( csSocket->socket, (struct sockaddr*)&client, &len);
        if (sock2 < 0) printf("Accept fehlgeschlagen");
	return(1);
}
