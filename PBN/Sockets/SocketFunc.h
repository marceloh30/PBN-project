#ifndef _SOCKETFUNC_H
#define _SOCKETFUNC_H

#include "../GeneralFunctions.h"
#include <sys/socket.h>
#include <netinet/in.h> // dirs de Socket
#include <arpa/inet.h> 	// 	"		"
#include <string.h>  //Para strchr


//Macros
#define SOCKET_ERROR -1

#define MAX_CLIENTS 8 //Maxima cantidad de clientes en el sistema
#define LOCALHOST "127.0.0.1"

#define MAXFDS 100 //Cantidad maxima de sockets en un select

#define BUF_SIZE 512 //largo de mensajes para los sockets

#define TIME_OUT 2
#define SEL_TIMEOUT 10

//-Puertos predefinidos
#define PUERTO_A 4028 

//Firmas
int sockEscuchar (uint16_t port);

int configurarSocketL (int sockId, struct sockaddr_in structSock, uint16_t puerto);

int sockAceptar (int sockId);

int sockConectar (char* dir, uint16_t port);

int selectSockets (int myreadfds[], int mywritefds[], int myexceptfd, long t_out, char *buff[], char *(*actRd)(char *, void *), void *shm, int (*actWr)(char *));

#endif
