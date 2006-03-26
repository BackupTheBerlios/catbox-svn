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
char *remote_hostname;
char *remote_client_type;
char *remote_client_version;
char rem_hostname[256];
char rem_client_type[20];
char rem_client_version[10];
int HandShake(int sockfd, char *buffer)
{
	printf("HandShake-Prozess gestartet...\n");
	ssize_t size;
	int success=0;
	strcpy(buffer,"CBW");
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
}
int main (int argc, char *argv[])
{
	remote_hostname = (char *)&rem_hostname[0];
	remote_client_type = (char *) &rem_client_type[0];
	remote_client_version =  (char *)&rem_client_version[0];
	int sockfd,new_fd;
	int bind_err,sockopt_err;
	const int y = 1;
	struct sockaddr_in local_addr;
	struct sockaddr_in remote_addr;
	ssize_t size;
	int sin_size;
	char *buffer = malloc(BUF);
		
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
	listen(sockfd,5);
	sin_size = sizeof(remote_addr);
	while(1)
	{
		new_fd = accept(sockfd, ( struct sockaddr *)&remote_addr, &sin_size);
		if(new_fd == -1)
		{
			perror("accept");
			continue;
		}
		printf("server: got connection from %s\n",inet_ntoa(remote_addr.sin_addr));
		int send_err,recv_err;
		HandShake(sockfd,buffer);
		printf("Hand Shake was successful!\n");
		do
		{
			fgets(buffer, BUF,stdin);
			send(new_fd,buffer,strlen(buffer),0);
			size = recv(new_fd,buffer,BUF-1,0);
			if(size > 0) buffer[size] = '\0';
			printf("Nachricht empfangen: %s \n",buffer);
		}while(strcmp(buffer,"quit\n") != 0);
		strcpy(buffer,"RHCC");
		buffer = buffer + '\0';
		send(new_fd,buffer,strlen(buffer),0);
		close (new_fd);
		exit(1);
		
	}
	close  (sockfd);
	return (1);
}
