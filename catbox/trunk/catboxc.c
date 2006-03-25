#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#define PORT 1234
#define SIGNALBUFFER 8192
static void error_exit(char *errorMessage)
{
    	fprintf(stderr, "%s: %s\n", errorMessage, strerror(errno));
	exit(EXIT_FAILURE);
}
int main(int argc, char **argv)
{
	printf("Starting CatBox Bash-Client...");
	printf("OK\n");
	int iSocket,iSocketA;
	int iSType,iSDomain;
	struct sockaddr_in server;
	struct hostent *host_info;
	unsigned long addr;
    	char *signal_string;
    	int signal_len;
	if (argc < 3)
        error_exit("Usage: client destination-ip signal\n");
	iSocket = socket(AF_INET,SOCK_STREAM,0);
	if(iSocket < 0)
	error_exit("Error creating Socket");
	memset( &server, 0, sizeof (server));
	if ((addr = inet_addr( argv[1])) != INADDR_NONE) 
	{
        	memcpy( (char *)&server.sin_addr, &addr, sizeof(addr));
	}
	else
	{
		host_info = gethostbyname(argv[1]);
		if (NULL == host_info)
            	error_exit("Unrecognized Server");
		memcpy( (char *)&server.sin_addr,host_info->h_addr, host_info->h_length );
		
	}
	server.sin_family = AF_INET;
	server.sin_port = htons( PORT );
	if(connect(iSocket,(struct sockaddr*)&server,sizeof(server)) <0)
        error_exit("Kann keine Verbindung zum Server herstellen");
	signal_string = argv[2];
	signal_len = strlen(signal_string);
 	if (send(iSocket, signal_string, signal_len, 0) != signal_len)
        error_exit("send() hat eine unterschiedliche Anzahl von Bytes versendet, als erwartet!");
	close(iSocket);
	return(1);
}
