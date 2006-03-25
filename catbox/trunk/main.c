#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "daemon.h"
int main (int argc, char *argv[])
{
	int iArgLocal,iArgType;
	CatSocket csSocket;
	printf("Starting CatBox-Daemon...");
	iInitNetwork(&csSocket);
	if(argc < 2)
	{
		iArgLocal = 1;
		iArgType = 1;
	}
	else if(argc >1)
	{
	iArgLocal = atoi(argv[1]);
	iArgType = atoi(argv[2]);
	}
	iSetUpSocket(&csSocket,iArgLocal,iArgType);
	printf("CatBox-Daemon ready for incoming connections.\n");
	/*for(;;)
	{
		iPollConnection(&csSocket);
	}*/
	return (1);
}
