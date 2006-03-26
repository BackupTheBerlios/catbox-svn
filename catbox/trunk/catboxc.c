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
#define CLIENT_VERSION "0.1"
char *hostnameptr;
char hostname;
int HandShake(int sockfd, char *buffer)
{
		//hostnameptr = &hostname;
		ssize_t size;
		int success=0;
		size = recv(sockfd,buffer,BUF-1,0);
		
		if(strcmp(buffer,"CBW") == 0)
		{
			if(size > 0)buffer[size]='\0';
			printf("%s empfangen, Server begr�sst uns. Wir senden Identifikationsstring...\n",buffer);
		}
		else
		{
			printf("Handshake fehlgeschlagen. Beende Verbindung!\n");
			close(sockfd);
			exit(1);
		}
		strcpy(buffer,"CBSTDC"); // CatBox Standard Client
		send(sockfd,buffer,strlen(buffer),0);
	do
	{
		size=recv(sockfd,buffer,BUF-1,0);
		if(size > 0)
		{
		if (strcmp(buffer,"CBCACK") == 0)
		{
				strcpy(buffer,CLIENT_VERSION);
				send(sockfd,buffer,strlen(buffer),0);
		}			
		if (strcmp(buffer,"CBHOST")== 0)
		{
				gethostname(hostname,256);
				strcpy(buffer,hostnameptr);
				send(sockfd,buffer,strlen(buffer),0);	
			
		}
		if (strcmp(buffer,"CBREADY")== 0)
		{
				printf("CatBox Daemon ist bereit! Starte Shell...\n");
				success=1;
		}
		}
		
		
	}while(success != 1);
}

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
	printf("Verbindung mit dem Server(%s) hergestellt...\n",inet_ntoa (remote_addr.sin_addr));
	//HandShake(sockfd,buffer);
	do
	{
		size = recv(sockfd,buffer,BUF-1,0);
		if(size > 0) buffer[size] = '\0';
		if(strcmp(buffer,"CBW")==0)
		{
				printf("CatBox-Daemon sagt Hallo...schicke Client-ID");
				strcpy(buffer,"CBID");
				send(sockfd,buffer,strlen(buffer),0);
		}
		size = recv(sockfd,buffer,BUF-1,0);
		if(size > 0) buffer[size] = '\0';
		if(strcmp(buffer,"RHCC")==0)
		{
			close(sockfd);
			exit(1);
		}
		if (strcmp(buffer,"quit\n") == 0)
		{

			send(sockfd,buffer,strlen(buffer),0);
		}
	}while(strcmp (buffer, "quit\n") != 0);
	close(sockfd);

	return (1);
}
