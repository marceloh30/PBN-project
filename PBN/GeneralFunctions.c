#include "GeneralFunctions.h"

int ejecProceso(char *dir, char *arg[]){
	
    int ret = -1;
    
    if( (ret = fork()) == 0 ) {

        if( execv(dir, arg) == -1 ){
			
            exit(0); //Si no se ejecuta, termina el proceso hijo (por fork)
		} 
		
    }
    /*- ret retorna el pid del proceso hijo, cuando el fork se realizo correctamente
      - ret = -1, si el fork no se realizo correctamente*/
	  
    return ret;
}

