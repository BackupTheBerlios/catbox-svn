#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main()
{
  struct sockaddr_in host_addr;
  int size;
  int s;
  struct hostent *host;
  char hostname[MAXHOSTNAMELEN];
  char buffer[1000];

  printf("\nEnter Hostname: ");
  scanf("%s",&hostname);

  host=gethostbyname(hostname);
  if (host==NULL)
    {
      fprintf(stderr, "Unknown Host %s\n",hostname);
      return -1;
    }

  fflush(stdout);
  /* Socket erzeugen */
  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0)
    {
      fprintf(stderr, "Error: socket\n");
      return -1;
    }
  /* Socket an das Ziel binden */
  host_addr.sin_family = AF_INET;
  host_addr.sin_addr = *((struct in_addr *)host->h_addr);
  host_addr.sin_port = htons(2199);
  /* Verbindung aufbauen */
  if (connect(s, (struct sockaddr *)&host_addr, sizeof(host_addr))==-1)
    {
      close(s);
      fprintf(stderr, "Error: connect\n");
      return -1;
    }
  /* Daten empfangen */
  size = recv(s, buffer, 1000, 0);
  if (size==-1)
    {
      close(s);
      fprintf(stderr, "reading data failed\n");
      return -1;
    }

  printf("Getting %d Bytes of Data\nData:%s\n",size,buffer);
  fflush(stdout);
  /* Socket wieder freigeben */
  close(s);
  return 0;
}
