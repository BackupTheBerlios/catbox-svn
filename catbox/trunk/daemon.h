#ifndef _DAEMON_H
#define _DAEMON_H
#include <stdbool.h>
#endif

typedef struct CatSocket
{
	bool (*sIsLocal)();
	int (*sConnect)(int,int,int);
	bool bLocal;
};

typedef struct CatDaemon 
{
	char test;
};

typedef struct
{
	char test;
}CatApp;
