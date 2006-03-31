#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <math.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#define PORT 1234
#define BUF 1024

int main(int argc, char *argv[])
{
	printf("\e[2J");
	int sockfd,connfd;
	socklen_t addrlen;
	const int y = 1;
	struct sockaddr_in localaddr;
	printf("Starte Server.\n");
	if(sockfd = socket(AF_INET, SOCK_STREAM, 0) == -1)
	{
		printf("Fehler beim Einrichten des Sockets!\n");
		exit(-1);
	}
	printf("Socket erstellt vom Typ AF_INET & SOCK_STREAM (TCP).\n");
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int));
	localaddr.sin_family = AF_INET;
	localaddr.sin_addr.s_addr = INADDR_ANY;
	localaddr.sin_port = htons(PORT);
	if (bind(sockfd, (struct sockaddr *)&localaddr,sizeof(localaddr)) != 0)
	{
		printf("Port %d belegt\n!",PORT);
		exit(-1);
	}
	printf("Socket ist online auf Port %s\n.",PORT);
	close(sockfd);
	printf("Socket geschlossen\n");
	return(1);
}
