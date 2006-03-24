#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
  int sockfd;                                   /* unsere Socket   */
  struct sockaddr_in my_addr, remote_addr;      /* 2 Adressen      */
  int remote_addr_size = sizeof(remote_addr);   /* fuer recvfrom() */
  char buf[1024];                               /* Datenpuffer     */

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
      fprintf(stderr, "Error: socket()\n");
      exit(1);
    }

  my_addr.sin_family      = AF_INET;
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  my_addr.sin_port        = htons(2199);

  if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0)
    {
      fprintf(stderr, "Error: bind()\n");
      close(sockfd);
      exit(1);
    }

  if (recvfrom(sockfd, buf, sizeof(buf), 0,
	       (struct sockaddr *)&remote_addr, &remote_addr_size) > 0)
    {
      printf("Getting Data from %s\n",
	     inet_ntoa(remote_addr.sin_addr.s_addr) );
      printf("Data : %s\n", buf);
    }
}
