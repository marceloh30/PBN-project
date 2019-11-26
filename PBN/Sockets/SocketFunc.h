#ifndef _SOCKETFUNC_H
#define _SOCKETFUNC_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //para Sleep
#include <sys/socket.h>
#include <netinet/in.h> // dirs de Socket
#include <arpa/inet.h> 	// 	"		"
#include <string.h>  //Para strchr


//Macros
#define SOCKET_ERROR -1

#define SEL_TIMEOUT 10

#define MAX_CLIENTS 8 //Maxima cantidad de clientes en el sistema
#define LOCALHOST "127.0.0.1"

#define MAXFDS 100 //Cantidad maxima de sockets en un select

#define BUF_SIZE 512 //largo de mensajes para los sockets

#define TIME_OUT 10

//-Acciones:
#define ACT_CREAR 0
#define ACT_BORRAR 1
#define ACT_SUSP 2
#define ACT_REAN 3
#define ACT_ENGAN 4
#define ACT_LISTA 5
#define ACT_EST 6

//-Filtros:
#define FILTRO_ALL 0
#define FILTRO_SP 1
#define FILTRO_SUSP 2
#define FILTRO_ACT 3 //(Activos o en ejec.)
#define FILTRO_EST 4

//-Puertos predefinidos
#define PUERTO_A 4028 



//Firmas
int sockEscuchar (uint16_t port);

int configurarSocketL (int sockId, struct sockaddr_in structSock, uint16_t puerto);

int sockAceptar (int sockId);

int sockConectar (char* dir, uint16_t port);

int selectSockets (int myreadfds[], int mywritefds[], int myexceptfd, long t_out, char *buff[], char *(*actRd)(char *), int (*actWr)(char *));

#endif
