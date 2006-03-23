#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "daemon.h"
int main (int argc, char **argv[])
{
	CatSocket csSocket;
	printf("Starting CatBox-Daemon...\n");
	iInitNetwork(csSocket);
	iSetUpSocket(csSocket,1,2);
	return (1);
} 
