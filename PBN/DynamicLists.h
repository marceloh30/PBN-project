#ifndef _DYNAMICLISTS_H_
#define _DYNAMICLISTS_H_

#include <stdlib.h>

typedef struct nodo {
	
	int data;
	struct nodo *next;

} Nodo;

typedef struct lista {

	int cant;
	struct nodo *first;

} Lista;

//Funciones para lista dinamica
Lista *crearLista (void);
Nodo *AgregarNodoPpio ( Lista *l, int data);
Nodo *ultimoNodo (Lista *l);
Nodo *agregarNodo (Lista *l, int data);
void liberarDatosLista (Lista *l);


#endif