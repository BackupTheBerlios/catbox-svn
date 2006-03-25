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
int main(int argc, char *argv[])
{
	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	struct hostent *he;
	struct sockaddr_in remote_addr;
	if(argc != 3)
	{
		fprintf(stderr,"Usage: client hostname msg\n");
		
	}
	if((he=gethostbyname(argv[1])) == NULL)
	{
		herror("gethostbyname");
		exit(1);
	}
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	remote_addr.sin_family = AF_INET;
	remote_addr.sin_port = htons(PORT);
	remote_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(remote_addr.sin_zero),8);
	if (connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("connect");
		exit(1);
	}


	if ((numbytes = recv(sockfd, buf, MAXDATASIZE,0)) == -1)
	{
		perror("recv");
		exit(1);
	}
	buf[numbytes] = '\0';
	printf("Received: %s\n", buf);
	if (strcmp(buf,"CBW") == 0) printf("Servers welcomes us. Sending fingerprint...\n");
	send(sockfd,"CSH",4,0);
	close(sockfd);

	return (1);
}
