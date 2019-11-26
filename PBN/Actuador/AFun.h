#ifndef _AFUN_H_
#define _AFUN_H_

#include "../Sockets/SocketFunc.h"
#include "../SHM/SHMFun.h"
#include "../GeneralFunctions.h"
#include <stdio.h>

#define WRITE_SOCK 1

typedef struct nodo {
	
	int data;
	struct nodo *next;

} Nodo;

typedef struct lista {

	int cant;
	struct nodo *first;

} Lista;

char *leerDatos (char *buf);
int getEstado (int pid); 
int devolverMsj (char *buf);

Lista *crearLista (void);
Nodo *AgregarNodoPpio ( ista *l, int data);
Nodo *ultimoNodo (Lista *l);
Nodo *agregarNodo (Lista *l, int data);
void liberarDatosLista (Lista *l);

#endif
