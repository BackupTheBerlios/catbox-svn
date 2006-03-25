#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#define PORT 1234
#define SIGNALBUFFER 8192
int iOutputSignal(int iSocket)
{
	char cBuffer[SIGNALBUFFER];
	int iRecvSize;
	time_t tTime;
	iRecvSize = recv(iSocket,cBuffer,SIGNALBUFFER,0);
	if(iRecvSize < 0)
	{
		printf("Couldn't receive message correctly!");
	}
	cBuffer[iRecvSize] = '\0';
	time(&tTime);
	printf("Message: %s \t%s",cBuffer,ctime(&tTime));
	return(1);
}
int main (int argc, char *argv[])
{
	int iSocket,iSocketA;
	int iSType,iSDomain;
	if(argc < 3)
	{
		iSDomain = AF_UNIX;
		iSType = SOCK_STREAM;
	}
	else
	{
	iSDomain = atoi(argv[1]);
	iSType = atoi(argv[2]);
	}
	struct sockaddr_in addr,client;
	socklen_t client_size;
	client_size = sizeof(client_size);
	switch(iSDomain)
	{
		case 1:
		iSDomain = PF_UNIX;
		break;
		case 2:
		iSDomain = PF_INET;
		break;
		default:
		break;
	}
	switch(iSType)
	{
		case 1:
		iSType = SOCK_STREAM;
		case 2:
		iSType = SOCK_DGRAM;
		default:
		break;
	}
	//iSocket = socket(iSDomain,iSType,IPPROTO_TCP);
	iSocket = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	memset( &addr, 0, sizeof (addr));
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);
	addr.sin_family = AF_INET; 
	
	if(bind(iSocket,(struct sockaddr*)&addr,sizeof(addr)) == -1)
	{
		printf("Couldn't bind Socket. Errorcode: %d\n",iSocket);
		exit(-1);
	}
	perror ("Socket bound...");
	if(listen(iSocket,5) == -1	)
	{
		fprintf(stderr,"listen() failed\n");
		exit(-1);
	
	}
	fprintf(stderr,"listening for services...");
	for(;;)
	{
        iSocketA = accept(iSocket,(struct sockaddr*)&client,&client_size);
	if(iSocketA == -1)
	{
		fprintf(stderr,"Accept from Client failed!\n");
		exit(1);
	}
	printf("Processing Client with the address %s, ",inet_ntoa(addr.sin_addr));
	iOutputSignal(iSocket);
	close(iSocket);
	//echo(iSocketA);
	//printf("telling us: %s",echo(iSocketA));
	}
	return (1);
}
