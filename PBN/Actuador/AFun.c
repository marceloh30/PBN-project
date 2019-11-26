#include "AFun.h"

char *leerDatos (char *buf){

	//Listas de prueba para mandar!
	char *lista = "1,5,7,23";
	char *listaSP = "s-1,s-5,p-7,p-23"; //1,5 creados por sesion y 7 y 23 por plan.
	char *listaSus= "5,7";	//5 y 7 susp.

	//Datos:
	int accion = atoi ( strtok (buf, ",") );
	int datoNum = atoi ( strtok (NULL, ",") ); //datoNum: Un filtro para lista o un pid determinado.
	char *data = strtok (NULL, ",");

	switch (accion) {



		case ACT_LISTA:
		
			if(datoNum == FILTRO_SP) {


			}










	}


}

void liberarDatos (Lista *l){
		
	Nodo *n = l -> first;
	
	while( n && n -> next) {
		
		free((void) n);
		n = n -> next;	
	}

	free( (void) (l -> first) );
	free( (void) (l) );
	
}

Lista *crearLista ( void ){

	Lista *l = (Lista *) malloc (sizeof(Lista));

	if (l != NULL) {

		l -> first = NULL;
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

