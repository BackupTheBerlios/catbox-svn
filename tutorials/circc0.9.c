/* Yep, those variables are actually the wierdest ... ever [I blame 
vodka - as always]  ... especially if you ain't speaking German.
But no worries if you ain't looking through this huge pile of C shit - 
I do neither - since like 2 weeks after I finished it :P */ 

#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
struct hostent *hostent;
struct sockaddr_in sockaddr;
int strumpf;
extern int fehla;
int wieschau; 
int hausnuma;
int socket_option=0;
char stoss[4096];
fd_set lesestrumpf;
struct zeitstrumpf;
#define RYTHMUS 30
time_t zeit,gestarted,letzter_kontakt,
 letzter_ping;
char deinname[64];
int stosszaler;
char rederaum[32];
char zeit_zeile[128];
int irc_port=6667;
char daten_form[255];
char rede_dienst_steller[128];
char spitzname[16];
int zeitrein;
int zeiger_zeile;
char stoss_rein_buffer[1024];
int raus_schrift;
char numma1[256]; 
char numma3[256];
char rein_stoss_terminal[1024];
int strumpf_rein_zahler; 
int zeiger_zeile;
char numma2[256];
int strumpf_rein_zeiger;
int raus_zeiger;




void versch_server_nachr(void)  
{
strumpf_rein_zeiger = 0;
raus_zeiger= 0;
while ((stoss_rein_buffer[strumpf_rein_zeiger] != ' ') &&
 (stoss_rein_buffer[strumpf_rein_zeiger] != 0))
  numma1[raus_zeiger++] = stoss_rein_buffer[strumpf_rein_zeiger++];
numma1[raus_zeiger] = 0;
numma2[0] = 0;
if (stoss_rein_buffer[strumpf_rein_zeiger])  
  {
  strumpf_rein_zeiger++;  
  raus_zeiger = 0;
  while ((stoss_rein_buffer[strumpf_rein_zeiger] != ' ') &&
   (stoss_rein_buffer[strumpf_rein_zeiger] != 0))
    numma2[raus_zeiger++] = stoss_rein_buffer[strumpf_rein_zeiger++];
  numma2[raus_zeiger] = 0;
  }
numma3[0] = 0;
if (stoss_rein_buffer[strumpf_rein_zeiger])  
  {
  strumpf_rein_zeiger++;
  raus_zeiger = 0;
  while ((stoss_rein_buffer[strumpf_rein_zeiger] != ' ') &&
   (stoss_rein_buffer[strumpf_rein_zeiger] != 0))
    numma3[raus_zeiger++] = stoss_rein_buffer[strumpf_rein_zeiger++];
  numma3[raus_zeiger] = 0;
  }
}



int main(int argc,char *argv[])
{
int wieviel;
wieviel = argc - 1;
printf("\n");
printf("Creepy`s IRC Client   -  CIRCC v.0.9  -       (c)by CreepyNodque\n");
printf("----------------------------)-:-(-------------------------------\n");
printf("----------------------)CreepyProducts.Tk(-----------------------\n");
printf("----------------------------)-:-(-------------------------------\n");
printf("\n");

if (wieviel < 3)             
  {
    printf("\n");
  printf("Enter the IRC server:       ");
  gets(rede_dienst_steller);
  printf("Enter your Nick:            ");
  gets(spitzname);
  printf("Enter Channel:              ");
  gets(rederaum);
  }
else
  {
  strcpy(rede_dienst_steller,argv[1]);
  strcpy(spitzname,argv[2]);
  strcpy(rederaum,argv[3]);
  }

gethostname(deinname,sizeof(deinname));


printf("(I´m connecting you now to %s with the nick %s.)\n",rede_dienst_steller,
 spitzname);
strcpy(zeit_zeile,rede_dienst_steller);
hostent = gethostbyname(zeit_zeile);  
if (hostent == NULL)
  {
  printf("Hey mate, check if the server is up.\n");
  return(1);
  }
strumpf = socket(AF_INET,SOCK_STREAM,0);  
if (strumpf < 0)
  {
  printf("That´s cinda creepy, we got problems with the sockets... =P\n");
  return(1);
    }
memset(&sockaddr,0,sizeof(sockaddr));  
sockaddr.sin_family = AF_INET;
memcpy((char *)&(sockaddr.sin_addr.s_addr),(char *)hostent->h_addr_list[0],
 (size_t)hostent->h_length);
sockaddr.sin_port = htons(irc_port);


if (connect(strumpf,(struct sockaddr *)&sockaddr,sizeof(sockaddr)) < 0)
  {
  printf("I can´t connect to the server buddy, I am sorry.\n");
  close(strumpf);
  return(1);
  }
fcntl(strumpf,F_SETFL,O_NONBLOCK);  
fcntl(1,F_SETFL,O_NONBLOCK);     




strcpy(stoss,"NICK ");
strcat(stoss,spitzname);
strcat(stoss,"\r\n");
write(strumpf,stoss,strlen(stoss));

strcpy(stoss,"USER ");
strcat(stoss,spitzname);
strcat(stoss," ");
strcat(stoss,deinname);
strcat(stoss," ");
strcat(stoss,rede_dienst_steller);
strcat(stoss," :Creepy´s IRC Client\r\n");
write(strumpf,stoss,strlen(stoss));

sleep(5);  

strumpf_rein_zahler   = 0;
stosszaler = 0;

gestarted = time((time_t *) 0);  
letzter_kontakt = time((time_t *) 0);  



event_loop:

raus_schrift = read(strumpf,stoss,1);  
if (raus_schrift == 1)  
  {
  if (stoss[0] == 13)   
    stoss[0] = 13;     
  if (stoss[0] != 10)   
    stoss_rein_buffer[strumpf_rein_zahler++] = stoss[0];
  if (stoss[0] == 10)   
    {
    stoss_rein_buffer[strumpf_rein_zahler] = 0;  
    strumpf_rein_zahler = 0;  
    letzter_kontakt = time((time_t *) 0);
    
    versch_server_nachr();
    if (!strncmp(stoss_rein_buffer,"PING",4))  
      {
     
      strcpy(stoss,stoss_rein_buffer);
      stoss[1] = 'O';
      strcat(stoss,"\r\n");
      write(strumpf,stoss,strlen(stoss));
      goto event_loop;
      }
    if (!strcmp(numma2,"PONG"))  
      goto event_loop;  
    if (!strcmp(numma2,"PRIVMSG"))  
      {
      printf("<");
      zeitrein = 1;
      while (numma1[zeitrein] != '!')
        printf("%c",numma1[zeitrein++]);
      printf("> ");
      while (stoss_rein_buffer[strumpf_rein_zeiger++] != ':')
        { };
      while (stoss_rein_buffer[strumpf_rein_zeiger] != 0)
        printf("%c",stoss_rein_buffer[strumpf_rein_zeiger++]);
      printf("\n");
      goto event_loop;
      }
    if (!strcmp(numma2,"001"))  
      {
      printf("(I gonna join %s now.)\n",rederaum);
      strcpy(stoss,"JOIN ");
      strcat(stoss,rederaum);
      strcat(stoss,"\r\n");
      write(strumpf,stoss,strlen(stoss));
      }
    printf("%s\n",stoss_rein_buffer);  
    }
  goto event_loop;
  }

raus_schrift = fgetc(stdin);  
if (raus_schrift != -1)  
  {
  if (raus_schrift == 13)   
    raus_schrift = 13;      
  if (raus_schrift != 10)   
    rein_stoss_terminal[stosszaler++] = raus_schrift;
  if (raus_schrift == 10)   
    {
    rein_stoss_terminal[stosszaler] = 0;  
    stosszaler = 0;  
    
    if (!strncmp(rein_stoss_terminal,"/quit",5))
      goto exit_point;
    if (rein_stoss_terminal[0] == '/')  
      {
      strcpy(stoss,rein_stoss_terminal+1);
      strcat(stoss,"\r\n");
      write(strumpf,stoss,strlen(stoss));
      goto event_loop;
      }
    strcpy(stoss,"PRIVMSG ");  
    strcat(stoss,rederaum);
    strcat(stoss," :");
    strcat(stoss,rein_stoss_terminal);
    strcat(stoss,"\r\n");
    write(strumpf,stoss,strlen(stoss));
    }
  goto event_loop;
  }

zeit = time((time_t *) 0);  
if (zeit - letzter_kontakt > 70)
  {
  printf("(Some problems accured... It´s the server´s fault, not mine!)\n");
  goto exit_point;
  }
if ((zeit - letzter_kontakt > RYTHMUS) &&
 (zeit - letzter_ping > RYTHMUS))
  {

  strcpy(stoss,"PING ");
  strcat(stoss,deinname);
  strcat(stoss,"\r\n");
  write(strumpf,stoss,strlen(stoss));
  letzter_ping = time((time_t*) 0);
  }
 
sleep(1);
goto event_loop;



exit_point:
printf("<CreepyNodque> Goodbye buddy, I hope you enjoyed using CIRCC!\n");
strcpy(stoss,"QUIT\r\n");  
write(strumpf,stoss,strlen(stoss));
shutdown(strumpf,2);           
close(strumpf);
return(0);
}

