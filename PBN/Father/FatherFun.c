#include "FatherFun.h"

int *crearProcSis( int puerto ) { //Devuelvo los pid para el cierre del sistema
    //Se inicializan los valores para evitar los warnigs
    int ret;
    int pidR = 0;
    int pidL = 0;
    int pidPM = 0;
    int pidA = 0;
    
    //Se obtienen los argumentos para ejecutar cada proceso
    char *port = NULL;
    sprintf(port,"%d",puerto);
	char *argR[] = { DIR_R, port, NULL };
	char *argL[] = { DIR_L, NULL };
	char *argPM[] = { DIR_PM, NULL };
	char *argA[] = { DIR_A, NULL };
	
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
	else{
		ret = EXIT_SUCCESS;
		pros = 4;
	}
    
    int retorno[]= {ret, pidR, pidL, pidPM, pidA};
    return retorno;
	
}

void eliminarSistema(int *pid, int id, void *shm, sem_t sem){
    //SIGTERM le indica a los procesos que se terminen

    struct timespec time = {2, 0};
    
    kill(pid[1],SIGTERM);
	nanosleep(time, NULL);
	if ( pros != 3) kill(pid[0], SIGKILL);
	
    kill(pid[2],SIGTERM);
	nanosleep(time, NULL);
	if ( pros != 2) kill(pid[1], SIGKILL); 	
	
	kill(pid[3],SIGTERM);
	nanosleep(time, NULL);
	if ( pros != 1) kill(pid[2], SIGKILL);
    	
	kill(pid[4],SIGTERM);
	nanosleep(time, NULL);
	if ( pros != 0) kill(pid[3], SIGKILL);
    
    desconectarSHM(shm);
    eliminarSemaforo(sem);
	eliminarSHM(id);
}

void signal_handler(int signal){
	if( signal == SIGCHLD){
		pros = pros - 1;
	}
}





