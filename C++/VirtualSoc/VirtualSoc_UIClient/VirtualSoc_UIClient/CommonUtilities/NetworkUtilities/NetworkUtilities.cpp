#include "NetworkUtilities.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <utility>
#include <cstdlib>
#include <cstring>
using namespace std;


int createBindedServerSocketToRandomPort(int *backPort, int N)
{
    int sd;
    int optval=1;
    struct sockaddr_in server;
    /* creare socket */
     if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
       {
         perror ("[server] Eroare la socket().\n");
         return errno;
       }

     /*setam pentru socket optiunea SO_REUSEADDR */
     setsockopt(sd, SOL_SOCKET, SO_REUSEADDR,&optval,sizeof(optval));

     /* pregatim structurile de date */
     bzero (&server, sizeof (server));

     /* umplem structura folosita de server */
     server.sin_family = AF_INET;
     server.sin_addr.s_addr = htonl (INADDR_ANY);
     server.sin_port = htons (0);

     /* atasam socketul */
     if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
       {
         perror ("[server] Eroare la bind().\n");
         return errno;
       }

     /* punem serverul sa asculte daca vin clienti sa se conecteze */
     if (listen (sd, N) == -1)
       {
         perror ("[server] Eroare la listen().\n");
         return errno;
       }

     if (backPort == NULL)
     {
         printf("Given null argument to createBindedServerSocketToRandomPort!");
         exit(1);
     }

     socklen_t len = sizeof(server);
     if(getsockname(sd, (struct sockaddr*)&server, &len) == -1)
     {
         printf("error at getsockname");
         exit(1);
     }

     *backPort = ntohs(server.sin_port);

     return sd;
}


int createBindedServerSocket(int PORT, int N)
{
    int sd;
    int optval=1;
    struct sockaddr_in server;
    /* creare socket */
     if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
       {
         perror ("[server] Eroare la socket().\n");
         return errno;
       }

     /*setam pentru socket optiunea SO_REUSEADDR */
     setsockopt(sd, SOL_SOCKET, SO_REUSEADDR,&optval,sizeof(optval));

     /* pregatim structurile de date */
     bzero (&server, sizeof (server));

     /* umplem structura folosita de server */
     server.sin_family = AF_INET;
     server.sin_addr.s_addr = htonl (INADDR_ANY);
     server.sin_port = htons (PORT);

     /* atasam socketul */
     if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
       {
         perror ("[server] Eroare la bind().\n");
         return errno;
       }

     /* punem serverul sa asculte daca vin clienti sa se conecteze */
     if (listen (sd, N) == -1)
       {
         perror ("[server] Eroare la listen().\n");
         return errno;
       }

     return sd;
}

int createConnectedClientSocket(char *address, int port)
{
    struct sockaddr_in server;
   int sd;
    /* cream socketul */
      if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
        {
          perror ("[client] Eroare la socket().\n");
          exit(1);
        }
      /* umplem structura folosita pentru realizarea conexiunii cu serverul */
      /* familia socket-ului */
      server.sin_family = AF_INET;
      /* adresa IP a serverului */
      server.sin_addr.s_addr = inet_addr(address);
      /* portul de conectare */
      server.sin_port = htons (port);

      /* ne conectam la server */
      if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
        {
          perror ("[client]Eroare la connect().\n");
          exit(1);
        }

    return sd;
}
