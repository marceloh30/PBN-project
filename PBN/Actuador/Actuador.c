#include "AFun.h"

int main ( int argc, char *argv[] ) {

	Lista *listaRps = crearLista(void);
	
	int readfds[100];
	int writefds[100];
	char *buffers[100];
	
	int newfd, sockEsc = sockEscuchar(PUERTO_A);
	int i;
	
	while(1) { //Curso normal
			
		newfd = selectSockets (readfds, writefds, sockEsc, SEL_TIMEOUT, buffers, leerDatos, devolverMsj);				
		
		if (newfd > 0) {
			
			agregarNodo (listaRps, newfd);				
			
			readfds[lista.cant] = newfd;
			writefds[lista.cant] = newfd;
			
		}	
		
	}

	close(sockEsc);
	liberarDatos(listaRps);
	
	return EXIT_SUCCESS;
}


