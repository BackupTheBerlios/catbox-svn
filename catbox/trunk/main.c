#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "daemon.h"
int main (int argc, char **argv[])
{
	CatSocket csSocket;
	printf("Starting CatBox-Daemon...\n");
	iInitNetwork(csSocket);
	int test;

	test = iSetUpSocket(csSocket,2,2); /* Soll derefenziert werden, hab ich gehört... seltsame Zahlen in Param. 2 & 3 */
	return (1);
}
