#ifndef _DAEMON_H
#define _DAEMON_H
#endif

typedef struct 
{
	int (*sIsLocal) ();
	int (*sConnect) (int,int,int);
	int iLocal;
	int socket;
	
}CatSocket;
typedef struct 
{
	char test;
}CatDaemon;

typedef struct
{
	int running;
}CatApp;
int iInitNetwork(CatSocket *csSocket);
int iSetUpSocket(CatSocket *csSocket, int iLocal, int iType);
int iIsLocal(CatSocket *csSocket);
int iPollConnection(CatSocket *csSocket);
