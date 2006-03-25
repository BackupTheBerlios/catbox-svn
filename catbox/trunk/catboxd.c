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


int main (int argc, char *argv[])
{
	int sockfd,new_fd;
	int bind_err;
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
	setsockopt( sockfd, SOL_SOCKET,SO_REUSEADDR, &y, sizeof(int));
	local_addr.sin_family = PF_INET;
	local_addr.sin_port = htons(PORT);
	local_addr.sin_addr.s_addr = INADDR_ANY;
	bind_err = bind(sockfd, (struct sockaddr *)&local_addr, sizeof(local_addr));
		
	if (bind_err == -1)
	{
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
		do
		{
			printf("Nachricht zum Versenden: ");
			fgets(buffer, BUF,stdin);
			send(new_fd,buffer,strlen(buffer),0);
			size = recv(new_fd,buffer,BUF-1,0);
			if(size > 0) buffer[size] = '\0';
			printf("Nachricht empfangen: %s \n",buffer);
		}while(strcmp(buffer,"quit\n") != 0);
		close (new_fd);
		
	}
	close  (sockfd);
	return (1);
}
