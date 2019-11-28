#include "ReceptorFun.h"

int delegarRecepc(char *userData, int sockId){

	
	int ret = 0;
	int rdsockId = -1;

	do{
		rdsockId = sockAceptar(sockId);

	} while (rdsockId < 0);


	int pidFork = fork();

	if (pidFork < 0) {

		close(rdsockId); //Cierro rdsockId: error

	} else {
		ret = 1; //Se creó clon correctamente.

		if (pidFork == 0) {

			// Estoy en hijo: Nuevo recepcionista.
			execl( DIRECCION_RP, DIRECCION_RP, &rdsockId, NULL);

		}
		else {
			// Estoy en padre: cierro socket en padre
			close(rdsockId);	
		}
	}

	return ret;

}

void escucharUsuarios(int puerto){
	
	int socket;

	while ( (socket = sockEscuchar(puerto)) < 0);


	//pid_t pidFork;
	delegarRecepc("user data",socket);
	
	close(socket);

}
