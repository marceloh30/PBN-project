#include "FatherFun.h"

int crearProcSis[]( int puerto ){ //Devuelvo los pid para el cierre del sistema

    int ret, pidR, pidL, pidMP, pidA; 
	char *argR[] = { DIR_R, &puerto, NULL };
	char *argL[] = { DIR_L, NULL };
	char *argPM[] = { DIR_PM, NULL };
	char *argA[] = { DIR_A, NULL };
	
	if( pidPM = ejecProceso(DIR_PM, argPM)) < 0 ){
		//No pude crear PM ni sistema.
		ret = EXIT_FAILURE;
		
	}
	
	else if ( (pidA = ejecProceso(DIR_A, argA)) < 0 ){
		
		kill(pidPM,SIGKILL);
		ret = EXIT_FAILURE;

	}
	
	else if ( (pidR = ejecProceso(DIR_R, argR)) < 0 ){
			
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
	pidL = -1; // Para que funcione correctamente 
	else ret = EXIT_SUCCESS;
	
	int retorno[] = {ret, pidR, pidL, pidMP, pidA};
	return retorno;
	
}





