#include "AFun.h"

int main ( int argc, char *argv[] ) {
	

	
	int sockEsc = sockEscuchar( PUERTO_A );
	
	Lista *l  = crearLista (void);
	int readfds[]={0, 0, 0, 0, 0};
	int writefds[]={0, 0, 0, 0, 0};

	while(1){ //curso normal
			
		selectSockets (readfds, writefds, sockEsc, SEL_TIMEOUT, char *buffer[], 1, accionSHM, devolverMsj);
				

	}

	close(sockEsc);

	return EXIT_SUCCESS;
}


