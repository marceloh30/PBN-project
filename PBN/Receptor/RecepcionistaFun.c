#include "RecepcionistaFun.h"







void cursoNormalRp(int socketC){
	
	int socketA = -1;

	//Para select:
	char buf1[BUF_SIZE], buf2[BUF_SIZE];
	char *buffs[] = {buf1, buf2}; 
	
	int rdsocks[]= {socketA, socketC, 0, 0, 0}; //Permito engancharme a 3 salidas.
	int wrsocks[]= {socketC, socketA};
	long time = 5; //Tiempo en segundos

	//Me conecto al bloque A	
	socketA = sockConectar(LOCALHOST, PUERTO_A); 
	
	//Opcional sin finalizar: 
	//falta dejar los ceros en rdsocks a lo ultimo al menos, o que buscar cantidad devuelva el proximo lugar libre.
	//int n;

	if (socketA > 0) {
		
		while(1) {			

			//selectSockets Lee en un socket y escribe en el otro:
			selectSockets (rdsocks, wrsocks, 0, SEL_TIMEOUT, buffs, 1,,x); 		
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
