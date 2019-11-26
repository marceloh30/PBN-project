#include "AFun.h"

int main ( int argc, char *argv[] ) {

	
	Lista *listaRps  = crearLista (void);
	int readfds[]={0, 0, 0, 0, 0};
	int writefds[]={0, 0, 0, 0, 0};
	int sockEsc = sockEscuchar( PUERTO_A );

	while(1){ //curso normal
			
		selectSockets (readfds, writefds, sockEsc, SEL_TIMEOUT, char *buffer[], 1, accionSHM, devolverMsj);
				

	}

	close(sockEsc);
	liberarDatos(listaRps);
	return EXIT_SUCCESS;
}


