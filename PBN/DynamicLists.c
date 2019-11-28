#include "DynamicLists.h"


//Liberar datos en heap de la lista:
void liberarDatosLista (Lista *l){
		
	Nodo *n = l -> first;
	
	while( n && n -> next) {
		
		free(n);
		n = n -> next;	
	}

	free( (l -> first) );
	free( (l) );
	
}

//Crear una lista:
Lista *crearLista ( void ){

	Lista *l = (Lista *) malloc (sizeof(Lista));

	if (l != NULL) {

		l -> first = NULL;
		l -> cant = 0;
	}	
	
	return l;
}

//Agregar nodo al principio:
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

//Ir al ultimo nodo de la lista:
Nodo *ultimoNodo ( Lista *l ){
	
	Nodo *n = l -> first;

	while( n && n -> next) {
		
		n = n -> next;	
	}
	
	return n;
}

//Agregar un nodo:
Nodo *agregarNodo ( Lista *l, int data ){
	
	Nodo *n = (Nodo *) malloc (sizeof(Nodo));

	if (n != NULL) {

		n -> data = data;
		n -> next = NULL;
		ultimoNodo (l) -> next = n;
	
		(l -> cant)++;
	}	
		
	return n;
}

