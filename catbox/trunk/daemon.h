#ifndef DAEMON_H
#define DAEMON_H
#include <stdbool.h>
#endif
typedef struct 
{
	bool (*sIsLocal) ();
	int (*sConnect) (int,int,int);
	bool bLocal;
}CatSocket;
typedef struct 
{
	char test;
}CatDaemon;

typedef struct
{

}CatApp;
