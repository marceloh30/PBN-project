#include "RecepcionistaFun.h"

void cursoNormalRp(int socketC) {
	
	int socketA = -1;

	int rdsocks[CANT_PROC];
	int wrsocks[2]; //Solo escribira en su terminal proporcionada y hacia A
	char *buffs[CANT_PROC];

	int newLx, cant = 2; //Cantidad de sockets de lectura

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
			newLx = selectSockets (rdsocks, wrsocks, 0, SEL_TIMEOUT, buffs, rdFun, NULL, wrFun); 	
			if (newLx > 0) {
				
				cant++;
				//rdsocks[cant-1] = newLx;
			
			}	
		}
		close(socketA);
		int i;
		for (i = 2; i == (cant - 1); i++) {
			close(rdsocks[i]);
		}
	}

	else {
		//Indico que hubo error al conectar A:
		char buf1[7];
		sprintf(buf1,"ErrorA");
		write(socketC, buf1, 7);		
		
	}

	close(socketC);

}


char *rdFun (char *buf, void *soyA, int socket) {
	
	const char retAr[BUF_SIZE];
	const char *ret = retAr;

	char bufTmp[BUF_SIZE];
	strcpy(bufTmp, buf);
	
	char *saveptr;
	
	int result = atoi(strtok_r(bufTmp, ",", &saveptr));
	//Interpreto mensaje:

	switch(result) {

		case 0: break;
		
		case WRITE_SOCK: {
			
			int caso = atoi(strtok_r(NULL, ",", &saveptr));
			if ( (caso == ACT_LISTA) || (caso == ACT_EST) || (caso == ACT_ENGAN) ) {
				ret = buf;
			}
			else { // caso == ACT_REAN || caso == ACT_SUSP || caso == ACT_BORRAR || otro caso (inexistente!)
				int datoNum = atoi(strtok_r(NULL, ",", &saveptr));
				sprintf(ret, "%d,%d", caso, datoNum);	
			}
			break;
		}

		case ERROR_A: {
			sprintf(ret,"Error al intentar crear proceso");
			break;
		}

		case ERROR_ACT: {
			sprintf(ret,"Error inesperado en pasaje acción");
			break;
		}
		

		default: {
			sprintf(ret,"Error inesperado en reenvio interno de mensajes");
		}

	}

	return ret;
}

int wrFun (char *buf, int socket) {

	return 1;
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
