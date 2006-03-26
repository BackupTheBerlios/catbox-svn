#include <netinet/ip.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <unistd.h>
#define SCHLUSS 65535
#define VARI 1
#define ANF 1
struct sockaddr_in addr;
struct hostent *rh;
struct servent *rp;
int strumpf,i;
int str_ptr, stp_ptr;
int Help(char *ARG);
int CONNECTION(int port);
int Help(char *ARG)
{
	fprintf(stderr,"LiLscan - (c) by C r e e p y N o d q u e - \n");
	fprintf(stderr,"-*******************__*******************- \n");
	fprintf(stderr,"Replacing both Start- and MaxPort with a +  results in a scan from 1-65535. \n");
	fprintf(stderr,"%s <hostname> [StartPort] [MaxPort] \n",ARG);
	exit(VARI);
}
int main(int argc, char *argv[])
{
	if (argc != 4)
		Help(argv[0]);
		str_ptr = atoi(argv[2]);
		stp_ptr = atoi(argv[3]);
	if (strcmp(argv[2],"+")==0 && strcmp(argv[3],"+")==0){
		str_ptr = ANF;
		stp_ptr = SCHLUSS;
	}
	if ( str_ptr > stp_ptr){
		fprintf(stderr,"Hey dude, try to choose a StartPort that is smaller than the MaxPort! \n");
		Help(argv[0]);
		exit(VARI);
	}
	if ((rh=gethostbyname(argv[1])) == NULL){		
		fprintf(stderr,"Check the host mate:I couldn´t find - %s -\n",argv[1]);
		Help(argv[0]);
		exit(VARI);
	}
	printf("I started scanning our victim %s! I will check if that jackass got any ports between %d and %d open! \n",argv[1],str_ptr,stp_ptr);
	for (i=str_ptr; i <= stp_ptr; i++)
	{
		if (CONNECTION(i)==0)
		{
			rp=getservbyport(htons(i),"tcp");
			printf("Port - %d - is open !!! On this port is usually the - %s - service running! \n",i,(rp == NULL)?"???":rp->s_name);
		}
	close(strumpf);
	}
return 0;
}
int CONNECTION(int port)
{
	if ((strumpf=socket(AF_INET,SOCK_STREAM,0)) == -1){
		perror("SockeT");
		exit(VARI);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr = *((struct in_addr *)rh->h_addr);
	if ((connect(strumpf,(struct sockaddr *) &addr, sizeof(addr))) == 0)
	return 0;
	else
		return 1;
}
