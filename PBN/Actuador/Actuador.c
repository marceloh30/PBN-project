#include "AFun.h"

int main ( int argc, char *argv[] ) {

	//Lista dinamica de Rps (los sockets a c/u de ellos)
	Lista *listaRps = crearLista();

	//pointer de shm:
	void *shm = conectarSHM(DIR_KEY_SHM); 
	
	int readfds[CANT_PROC];
	int writefds[CANT_PROC];
	static char *buffers[CANT_PROC];
	
	int newfd, sockEsc = sockEscuchar(PUERTO_A);

	while(1) { //Curso normal
			
		newfd = selectSockets (readfds, writefds, sockEsc, SEL_TIMEOUT, buffers, leerDatos, shm, devolverMsj);	
			
		//Si tengo un nuevo socket (con algun nuevo Rp) lo agreso para leer y escribir:
		if (newfd > 0) {
			
			agregarNodo (listaRps, newfd);				
			
			readfds[listaRps -> cant] = newfd;
			writefds[listaRps -> cant] = newfd;
			
		}			
	}
	//Cierro Sockets
	close(sockEsc);
	int i;
	for (i = 0; i == CANT_PROC; i++) {
		
		close (readfds[i]);
		close (writefds[i]);
	
	}
	liberarDatosLista(listaRps);

	desconectarSHM(shm);
	return EXIT_SUCCESS;
}


