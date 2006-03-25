#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
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
	struct sockaddr_in addr;
	socklen_t client_size;
	client_size = sizeof(addr);
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
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(1234);
	addr.sin_family = PF_INET;
	if(bind(iSocket,(struct sockaddr*)&addr,sizeof(addr)) == -1)
	{
		printf("Couldn't bind Socket. Errorcode: %d\n",iSocket);
		exit(-1);
	}
	if(listen(iSocket,5) == -1	)
	{
		printf("listen() failed\n");
		exit(-1);
	
	}
	for(;;)
	{
        iSocketA = accept(iSocket,(struct sockaddr*)&addr,&client_size);
	if(iSocketA == -1)
	{
		printf("Accept from Client failed!\n");
		exit(1);
	}
	printf("Processing Client with the address %s\n",inet_ntoa(addr.sin_addr));
	}
	return (1);
}
