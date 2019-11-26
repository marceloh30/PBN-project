#include "FatherFun.h"

int *crearProcSis( int puerto ){ //Devuelvo los pid para el cierre del sistema
    int ret;
    int retorno[];
    
    //-----// Se inicializan los valores para evitar los warnigs
    int pidR = 0;
    int pidL = 0;
    int pidPM = 0;
    int pidA = 0;
    //-----//
    
    //-----// Se definen los argurmentos para cada proceso
    char *port = NULL;
    sprintf(port,"%d",puerto);
	char *argR[] = { DIR_R, port, NULL };
	char *argL[] = { DIR_L, NULL };
	char *argPM[] = { DIR_PM, NULL };
	char *argA[] = { DIR_A, NULL };
    //-----//
	
	if( (pidPM = ejecProceso(DIR_PM, argPM)) < 0 ){
		//No pude crear PM ni sistema.
		ret = EXIT_FAILURE;
		
	} else if ( (pidA = ejecProceso(DIR_A, argA)) < 0 ){
		
		kill(pidPM,SIGKILL);
		ret = EXIT_FAILURE;

	} else if ( (pidR = ejecProceso(DIR_R, argR)) < 0 ){
			
		kill(pidPM,SIGKILL);
		kill(pidA,SIGKILL);
		ret = EXIT_FAILURE;
		
	}
	
	/* -> Ir Haciendo...

	else if( (pidL = ejecProceso(DIR_L, argL)) < 0 ){

		kill(pidPM,SIGKILL);	
		kill(pidA,SIGKILL);
		kill(pidR,SIGKILL);	
		ret = EXIT_FAILURE;
		
    }
	*/
    // Para que funcione correctamente
	else ret = EXIT_SUCCESS;
    pidL = -1;  // Para que funcione correctamente
    
    retorno[] = {ret, pidR, pidL, pidPM, pidA};
    return retorno;
	
}

void eliminarSistema(int *pid, int id, void *shm){
    //SIGTERM le indica a los procesos que se terminen
    kill(pid[0],SIGTERM);
    kill(pid[1],SIGTERM);
    kill(pid[2],SIGTERM);
    kill(pid[3],SIGTERM);
    perror("Error al eliminar el sistema: ");
    eliminarSHM(id);
    desconectarSHM(shm);
}





