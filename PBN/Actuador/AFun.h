#ifndef _AFUN_H_
#define _AFUN_H_

#include "../Sockets/SocketFunc.h"
#include <stdio.h>

typedef struct nodo {
	
	int data;
	struct nodo *next;

} Nodo;

typedef struct lista {

	int cant;
	struct nodo *first;

} Lista;

char *leerDatos (char *buf);
void escribirDatos (char *buf);
Lista *crearLista ( void );
Nodo *AgregarNodoPpio ( Lista *l, int data );
Nodo *ultimoNodo ( Lista *l );
Nodo *agregarNodo ( Lista *l, int data );

#endif
