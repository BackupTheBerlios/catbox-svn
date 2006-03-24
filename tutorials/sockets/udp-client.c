#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char **argv)
{
  int sockfd;
  struct sockaddr_in my_addr, remote_addr;
  struct hostent *host_addr;

  if (argc != 3)
    {
      fprintf(stderr, "Usage: %s [HOST] [MESSAGE]\n", argv[0]);
    }

  if ((host_addr = gethostbyname(argv[1])) == NULL)
    {
      fprintf(stderr, "Cannot resolv hostname: %s\n", argv[1]);
      exit(1);
    }

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
      fprintf(stderr, "Error: socket()\n");
      exit(1);
    }

  remote_addr.sin_family = AF_INET;
  remote_addr.sin_addr   = *((struct in_addr *) host_addr->h_addr);
  remote_addr.sin_port   = htons(2199);

  if (sendto(sockfd, argv[2], strlen(argv[2]) + 1, 0,
	     (struct sockaddr *)&remote_addr, sizeof(remote_addr)) > 0)
    {
      printf("Message sent\n");
    } else {
      fprintf(stderr, "Error while sending data\n");
    }
  close(sockfd);
}
