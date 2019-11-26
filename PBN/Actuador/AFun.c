#include "AFun.h"

char *leerDatos (char *buf) {
	
	char bufTmp[BUF_SIZE];
	strcpy(bufTmp, buf);
	
	//Listas de prueba para mandar!
	char *lista = "1,5,7,23";
	char *listaSP = "s-1,s-5,p-7,p-23"; //1,5 creados por sesion y 7 y 23 por plan.
	char *listaSus = "5,7";	//5 y 7 susp.
	char *listaAct = "1, 23";
	
	char ret[BUF_SIZE];
	char *pret = ret;
	
	//Datos:
	int accion = atoi ( strtok_r (bufTmp, ",", &saveptr) );
	int datoNum = atoi ( strtok_r (NULL, ",", &saveptr) ); //datoNum: Un filtro para lista o un pid determinado.
	char *data = strtok_r (NULL, ",", &saveptr);
	int socket = atoi ( strtok_r (NULL, ",", &saveptr) ); //Para devolverle el dato a ese socket.
	
	int paraWrite = 0; //Lo dejo en 0 para que sea false (al no ser que lo cambie el código)
	
	switch (accion) {
		
		case ACT_LISTA: {
			paraWrite = WRITE_SOCK;
			switch (datoNum) {
				
				case FILTRO_SP: {
					//Hacer lectura de lista!
					sprintf(pret, "%d%s\n", paraWrite, listaSP);
					break;
				}	
				case FILTRO_SUSP: {
					//same
					sprintf(pret, "%d%s\n", paraWrite, listaSus);
					break;
				}
				case FILTRO_ACT: {
					
					sprintf(pret, "%d%s\n", paraWrite, listaAct);
					break;
				}
				case FILTRO_ALL: {
					
					sprintf(pret, "%d%s\n", paraWrite, lista);
					break;
				}
				case DEFAULT: {
					
					sprintf(pret, "%d%s\n(DEFAULT)\n", paraWrite, lista); 
					break;
				}
			}
		}
		
		case ACT_ESTADO: {
			paraWrite = WRITE_SOCK;
			sprintf(pret, "%d,%d", paraWrite, getEstado(datoNum));
			break;
		}
		
		case ACT_ENGAN: {
			paraWrite = WRITE_SOCK;
			sprintf(pret, "%d,%s", paraWrite, "To-do ENGAN");	
			break;
		}
		
		case ACT_REAN: {
			
			sprintf(pret, "%s", "To-do REAN");	
			break;
		}
		
		case ACT_SUSP: {
			
			sprintf(pret, "%s", "To-do SUSP");	
			break;
		}
		
		case ACT_CREAR: { 
			
			sprintf(pret, "%s", "To-do CREAR");	
			break;
		}
		
		case ACT_BORRAR: {
			
			sprintf(pret, "%s", "To-do BORRAR");	
			break;
		}
		
		default: {
			
			sprintf(pret, "%s", "To-do DEFAULT");	
			break;
			
		}
	}
	
	return pret;
}

int devolverMsj (char *buf) {
	
	return ( atoi(buf[0]) == WRITE_SOCK ) ? 1 : 0;
}

int getEstado(int pid){
	
	return pid;
}

void liberarDatosLista (Lista *l){
		
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

