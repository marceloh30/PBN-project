#include "AFun.h"

char *leerDatos (char *buf){
	
	int pid = atoi ( strtok (buf, ",") );
	char *data = strtok (buf, ",");
	int estado = atoi ( strtok (buf, ",") );
	char *creador = buf;

	
	
}


Lista *crearLista ( void ){

	Lista *l = (Lista *) malloc (sizeof(Lista));

	if (l != NULL) {

		l -> first = l -> last = NULL;
		l -> cant = 0;
	}	
	
	return l;
}

Nodo *AgregarNodoPpio ( Lista *l, int data ){
	
	Nodo *n = (Nodo *) malloc (sizeof(Nodo));

	if (n != NULL) {

		n -> data = data;
		n -> next = l -> first;
		l -> first = n;
		(l -> cant)++;
	}

	return n;

}


Nodo *ultimoNodo ( Lista *l ){
	
	Nodo *n = l -> first;

	while( n && n -> next) {
		
		n = n -> next;	
	}
	
	return n;
}

Nodo *agregarNodo ( Lista *l, int data ){
	
	Nodo *n = (Nodo *) malloc (sizeof(Nodo));

	if (n != NULL) {

		n.data = data;
		n.last = NULL;
		Nodo *nLast = ultimoNodo (l);

		nLast.next = n;
	
		(l.cant)++;
	}	
		
	return n;
}

