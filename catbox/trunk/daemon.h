#ifndef DAEMON_H
#define DAEMON_H
#include <stdbool.h>
#endif

typedef struct 
{
	int (*sIsLocal) ();
	int (*sConnect) (int,int,int);
	int iLocal;
}CatSocket;
typedef struct 
{
	char test;
}CatDaemon;

typedef struct
{

}CatApp;
int iInitNetwork(CatSocket *csSocket);
int iSetUpSocket(CatSocket *csSocket, int iLocal, int iType);
int IsLocal(CatSocket *csSocket);
