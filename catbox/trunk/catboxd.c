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
#include <sys/wait.h> 
#define PORT 1234
#define BUF 1024
#define BACKLOG 10
/*char *remote_hostname=NULL;
char *remote_client_type=NULL;
char *remote_client_version=NULL;*/
/*
int HandShake(int *sockfd, char  *buffer)
{
	ssize_t size;
	int success=0;
	printf("Buffer: %p\n",buffer);
	strcpy(buffer,"CBW");
	printf("HandShake-Prozess gestartet...\n");
	
	send(sockfd,buffer,BUF-1,0);
	printf("CBW gesendet..\n");
	size = recv(sockfd,buffer,BUF-1,0);
	do
	{
	if (strcmp(buffer,"CBSTDC") == 0)
	{
			strcpy(remote_client_type,buffer);
			printf("Standard client recognized! Connection accepted...\n");
			strcpy(buffer,"CBCACK");
			send(sockfd,buffer,BUF-1,0);
			size = recv(sockfd,buffer,BUF-1,0);
			strcpy(remote_client_version,buffer);
			if(size>0) remote_client_version[size] = '\0';
			size = recv(sockfd,buffer,BUF-1,0);
			strcpy(buffer,"CBCHOST");
			send(sockfd,buffer,BUF-1,0);
			size = recv(sockfd,buffer,BUF-1,0);
			strcpy(remote_hostname,buffer);
			if(size>0) remote_hostname[size] = '\0';
			printf("Remote (%s) uses a standard CatBox Client using version %s\n.",remote_hostname,remote_client_version);
			strcpy(buffer,"CBREADY");
			send(sockfd,buffer,BUF-1,0);
			success =1;
	}
	}while(success!=1);
	//if(size > 0)buffer[size]='\0';
	
	
	return(1);
}*/
int main (int argc, char *argv[])
{
	char welcome[]= "Welcome to the CBDS console!";
	/*char rem_hostname[256];
char rem_client_type[20];
char rem_client_version[10];
	remote_hostname = (char *)&rem_hostname[0];
	remote_client_type = (char *) &rem_client_type[0];
	remote_client_version =  (char *)&rem_client_version[0];*/
	int sockfd,new_fd;
	int bind_err,sockopt_err;
	const int y = 1;
	struct sockaddr_in local_addr;
	struct sockaddr_in remote_addr;
	ssize_t size;
	int sin_size;
	char *buffer = malloc(BUF);
	printf("Buffer: %p\n",buffer);
	if ((sockfd = socket(PF_INET, SOCK_STREAM,0)) == -1)
	{
		perror("socket");
		exit(1);
	}
	printf("Socket angelegt...\n");
	
	sockopt_err = setsockopt( sockfd, SOL_SOCKET,SO_REUSEADDR, &y, sizeof(int));
	if(sockopt_err == -1)
	{
		printf("Socket-Optionen schlagen fehl!\n");
		exit(1);
	}
	local_addr.sin_family = PF_INET;
	local_addr.sin_port = htons(PORT);
	local_addr.sin_addr.s_addr = INADDR_ANY;
	bind_err = bind(sockfd, (struct sockaddr *)&local_addr, sizeof(local_addr));
		
	if (bind_err == -1)
	{
		perror("bind");
		printf("Port belegt!\n");
		exit(1);
	}
	printf("Bind executed normally...\n");
	listen(sockfd,100);
	sin_size = sizeof(remote_addr);
	int success=0;
	while(1 || success ==1)
	{
		new_fd = accept(sockfd, ( struct sockaddr *)&remote_addr, &sin_size);
		if(new_fd == -1)
		{
			perror("accept");
			continue;
		}
		printf("server: got connection from %s\n",inet_ntoa(remote_addr.sin_addr));
		int send_err,recv_err;
		/*HandShake(&sockfd, buffer);
		printf("Hand Shake was successful!\n");*/
		do
		{
			printf("Sende HandShake-Gruss. Warte auf Client-Identifizierung.\n");
			strcpy(buffer,"CBW");
			send(new_fd,buffer,strlen(buffer),0);
			size = recv(new_fd,buffer,BUF-1,0);
			if(strncmp(buffer,"CBID",4) == 0)
			{
				if(size > 0) buffer[size] = '\0';
				printf("Standard-Client erkannt.\n Schicke Bestaetigung an Client, HandShake abgeschlossen.\n",buffer);
				strncpy(buffer,"CBACK",5);
				send(new_fd,buffer,strlen(buffer),0);
				printf("Starte CBDS...\n");
				success = 1;
			}
			
		}while(success != 1);
		success = 0;
		/* Shell zu Client senden */

			
		write(sockfd,"RHCC",4);
		send(new_fd,buffer,strlen(buffer),0);
		close (new_fd);
		exit(1);
		
	}
	printf("\nBeende CBDS.!\n");
	close  (sockfd);
	return (1);
}
