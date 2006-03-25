#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#define PORT 1234
#define MAXDATASIZE 100
#define BUF 1024
int main(int argc, char *argv[])
{
	int sockfd, numbytes;
	ssize_t size;
	char buf[MAXDATASIZE];
	char *buffer=malloc(BUF);
	struct hostent *he;
	struct sockaddr_in remote_addr;
		
	if(argc != 2)
	{
		fprintf(stderr,"Usage: client hostname \n");
		
	}
	
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	if(sockfd > 0)printf("Socket wurde korrekt angelegt\n");
	remote_addr.sin_family = AF_INET;
	remote_addr.sin_port = htons(PORT);
	inet_aton (argv[1], &remote_addr.sin_addr);
	if (connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("connect");
		exit(1);
	}
	printf("Verbindung mit dem Server(%s) hergestellt...\n",inet_ntoa(remote_addr.sin_addr));
	do
	{
		size = recv(sockfd,buffer,BUF-1,0);
		if(size > 0) buffer[size] = '\0';
		printf("Nachricht empfangen: %s\n",buffer);
		if (strcmp(buffer,"quit\n"))
		{
			printf("Nachricht zum Versenden: ");
			fgets(buffer,BUF,stdin);
			send(sockfd,buffer,strlen(buffer),0);
		}
	}while(strcmp (buffer, "quit\n") != 0);
	close(sockfd);

	return (1);
}
