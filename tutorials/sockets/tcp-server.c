#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>

int main()
{
  struct sockaddr_in my_addr;
  struct sockaddr_in remote_addr;
  int size;
  int s;
  int remote_s;

  /* Die Socket erzeugen */
  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0)
    {
      fprintf(stderr, "Error: Socket\n");
      return -1;
    }

  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(2199); /* Port 2199 */
  my_addr.sin_addr.s_addr = INADDR_ANY; /* An jedem Device warten */

  if (bind(s, (struct sockaddr *)&my_addr, sizeof(my_addr))==-1)
    {
      close(s);
      fprintf(stderr, "Error: bind\n");
      return -1;
    }

  /* Socket aufs warten vorbereiten */
  if (listen(s, 1)==-1)
    {
      fprintf(stderr, "Error: listen\n");
      return -1;
    }

  fflush(stdout);
  size=sizeof(remote_addr);
  /* Auf eine eingehende Verbindung warten */
  remote_s = accept(s, (struct sockaddr *)&remote_addr, &size);
  fflush(stdout); /* Ausgabepuffer leeren */
  if (remote_s < 0)
    {
      close(s);
      fprintf(stderr, "Error: accept\n");
      return -1;
    }
  /* Daten ueber seinen Gegenueber ausgeben */
  printf("\nincoming connection from %s\n",
      inet_ntoa(remote_addr.sin_addr.s_addr));
  printf("sending data...");
  fflush(stdout);
  size=send(remote_s, "Hello World",11,0);
  if (size==-1)
    {
      fprintf(stderr, "error while sending\n");
    } else {
      printf("ready\n%d Bytes send to remote host\n", size);
    }
  printf("closing sockets\n");
  /* Sockets wieder freigeben */
  close(remote_s);
  close(s);
  printf("terminating\n");
  fflush(stdout);
  return 0;
}
