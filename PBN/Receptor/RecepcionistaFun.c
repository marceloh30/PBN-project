#include "RecepcionistaFun.h"

void cursoNormalRp(int socketC){
	
	int socketA = -1;

	int rdsocks[100];
	int wrsocks[100];
	char *buffs[100];
		
	rdsocks[0] = wrsocks[1] = socketA; 
	rdsocks[1] = wrsocks[0] = socketC; 
	
	//Me conecto al bloque A	
	socketA = sockConectar(LOCALHOST, PUERTO_A); 
	
	//Opcional sin finalizar: 
	//falta dejar los ceros en rdsocks a lo ultimo al menos, o que buscar cantidad devuelva el proximo lugar libre.
	//int n;

	if (socketA > 0) {
		
		while(1) {			
			//selectSockets Lee en un socket y escribe en el otro:
			selectSockets (rdsocks, wrsocks, 0, SEL_TIMEOUT, buffs, rdFun,(void *) NULL, wrFun); 		
/* ->Para opcional...
			while (ret && ret[0]) {

				lectura = strtok(ret, "-");

				if ( (n = buscarCantidad(rdsocks)) < 5 ){
					//Tomo valor de fd e ignoro letra porque solamente puede ser de lectura aqui.
					rdsocks[5-n-1] = atoi(lectura[1]); 
				}
				else {
					write(socketC, "ErrorLxMax", 11);
				}

				
			}
*/

		}

		
		close(socketA);
	}

	else {
		//Indico que hubo error al conectar A:
		sprintf(buf1,"ErrorA");
		write(socketC, buf1, 7);		
		
	}

	close(socketC);




}


char *rdFun (char *buf) {


	return buf;
}

int wrFun (char *buf);


	return 0;
}
/*
int buscarCantidad(int array[]){

	int ret = 0, i;
	int size = sizeof( &array ) / sizeof( array[0] );
	
	for(i = 0; i < size; i++){
		
		if ( array[i] > 0 ){
			ret++;
		}			
	}	
	
	return ret;
}
*/
