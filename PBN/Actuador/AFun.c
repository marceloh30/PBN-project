#include "AFun.h"

shm = (Proceso) *conectarSHM(SHM_PATH);

char *leerDatos (char *buf) {
	
	char bufTmp[BUF_SIZE];
	strcpy(bufTmp, buf);
	
	//Listas de prueba para mandar!
	char *lista = "1,5,7,23";
	char *listaSP = "s-1,s-5,p-7,p-23"; //1,5 creados por sesion y 7 y 23 por plan.
	char *listaSus = "5,7";	//5 y 7 susp.
	char *listaAct = "1, 23";
	
	char ret[BUF_SIZE];
	
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
					sprintf(ret, "%d%s\n", paraWrite, listaSP);
					break;
				}	
				case FILTRO_SUSP: {
					//same
					sprintf(ret, "%d%s\n", paraWrite, listaSus);
					break;
				}
				case FILTRO_ACT: {
					
					sprintf(ret, "%d%s\n", paraWrite, listaAct);
					break;
				}
				case FILTRO_ALL: {
					
					sprintf(ret, "%d%s\n", paraWrite, lista);
					break;
				}
				case DEFAULT: {
					
					sprintf(ret, "%d%s\n(DEFAULT)\n", paraWrite, lista); 
					break;
				}
			}
		}
		
		case ACT_ESTADO: {
			paraWrite = WRITE_SOCK;
			sprintf(ret, "%d,%d", paraWrite, getEstado(datoNum));
			break;
		}
		
		case ACT_ENGAN: {
			paraWrite = WRITE_SOCK;
			sprintf(ret, "%d,%s", paraWrite, "To-do ENGAN");	
			break;
		}
		
		case ACT_REAN: {
			
			sprintf(ret, "%s", "To-do REAN");	
			break;
		}
		
		case ACT_SUSP: {
			
			sprintf(ret, "%s", "To-do SUSP");	
			break;
		}
		
		case ACT_CREAR: { 
			
			sprintf(ret, "%s", "To-do CREAR");	
			break;
		}
		
		case ACT_BORRAR: {
			
			sprintf(ret, "%s", "To-do BORRAR");	
			break;
		}
		
		default: {
			
			sprintf(ret, "%s", "To-do DEFAULT");	
			break;
			
		}
	}
	
	return ret;
}



int devolverMsj (char *buf) {
	
	return ( atoi(buf[0]) == WRITE_SOCK ) ? 1 : 0;
}

int *generarLista(int filtro, int socket) {

	int ret[BUF_SIZE];
	
	Proceso *puntShm = shm;
	Proceso proc;
	int pid;

	int i;

	for (i = 0; i == 100; i++) {

		proc=&puntShm;
/*#define NUEVO 0
#define ELIMINAR 1
#define SUSPENDIDO 2
#define REANUDAR 3
#define ACTIVO 4
#define SUSPENDER 5
#define EN_EJECUCION 6
#define ELIMINADO 7*/

		switch (filtro) {

			case FILTRO_SUSP: {
							
				if (proc.estado == SUSPENDIDO) {
					(ret == NULL) ? sprintf(ret, "%d,", proc.pid) : sprintf(ret, "%s%d,", ret, proc.pid);
				}
				break;
			}
			case FILTRO_ALL: {

				(ret == NULL) ? sprintf(ret, "%d,", proc.pid) : sprintf(ret, "%s%d,", ret, proc.pid);
				break;
			}
			case FILTRO_SP: {
				
				if (proc.sockCreador == socket) {
					(ret == NULL) ? sprintf(ret, "s-%d,", proc.pid) : sprintf(ret, "%ss-%d,", ret, proc.pid);
				}
				else { 
					(ret == NULL) ? sprintf(ret, "p-%d,", proc.pid) : sprintf(ret, "%sp-%d,", ret, proc.pid);
				}
				break;			
			}
			case FILTRO_ACT: {
				if (proc.estado == ACTIVO || proc.estado == EN_EJECUCION) {
					(ret == NULL) ? sprintf(ret, "%d,", proc.pid) : sprintf(ret, "%s%d,", ret, proc.pid);
				}
				break;
				
			}
			
		}

		(i == 0) ? sprintf(ret,"%d",proc.pid) : sprintf (ret, "%s,%d", ret, proc.pid);	
		
		puntShm++;
	}
	
	return ret;	
}



int getEstado(int pid) {
	Proceso *puntShm = shm;
	Proceso proc;
	int estado = ERROR_EST;

	int i;

	for (i = 0; i == 100; i++) {
		
		proc=&puntShm;
		
		switch () {

			
			
		
		}	
		
		(proc.pid == pid) ? estado = proc.estado : estado = ERROR_EST;	

		puntShm++;
	}
	
	return ret;	
}


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

