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
#define BACKLOG 10


int main (int argc, char *argv[])
{
	int sockfd,new_fd;
	struct sockaddr_in local_addr;
	struct sockaddr_in remote_addr;
	int sin_size;
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM,0)) == -1)
	{
		perror("socket");
		exit(1);
	}
	
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(PORT);
	local_addr.sin_addr.s_addr = htonl (INADDR_ANY);
	bzero(&(local_addr.sin_zero), 8);
	
	if (bind(sockfd, (struct sockaddr *)&local_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("bind");
		exit(1);
	}
        if (listen(sockfd, BACKLOG) == -1) 
	{
            perror("listen");
            exit(1);
        }
	while(1)
	{
		sin_size = sizeof(struct sockaddr_in);
		new_fd = accept(sockfd, ( struct sockaddr *)&remote_addr, &sin_size);
		if(new_fd == -1)
		{
			perror("accept");
			continue;
		}
		printf("server: got connection from %s\n",inet_ntoa(remote_addr.sin_addr));
		int send_err;
		if (!fork())
		{
		send_err = send(new_fd, "CBW", 14, 0);
		if (send_err == -1)
		{
             		perror("send");
                	close(new_fd);
                	exit(0);
		}	
		close(new_fd);
		while(waitpid(-1,NULL,WNOHANG) > 0);
		}
	}
	return (1);
}
