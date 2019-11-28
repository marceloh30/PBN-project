#include "ComConsola.h"


int conectarSist(int *dir, int timeOut){
	
	char ip[40];

	clock_t tStart, tEnd;
    	unsigned int tiempo = 0;
	tStart = clock();

	int wrsocket = -1;

	sprintf(ip, "%d.%d.%d.%d", dir[0], dir[1], dir[2], dir[3]); //Guardo ip con formato char * !!	
	
	printf("Intento conexion a %s:%d!\n", ip, dir[4]);

	if ( wrsocket ) { 
		
		do {
			wrsocket = sockConectar(ip, dir[4]);
			tEnd = clock();
			tiempo = (unsigned int)(tEnd - tStart);
		} while ( (wrsocket < 0) && (tiempo < 1000000) );
		
	}

	return wrsocket;
}


char *enviarAccion ( int accion, int datoNum, char *datos, int socket ) {
	
	char *ret;
	
	char msj[BUF_SIZE];
	sprintf(msj, "%d,%d,%s,%d", accion, datoNum, datos, socket); //Envío socket para que se sepa a quien responder en A.
	
	if ( (write(socket, msj, BUF_SIZE)) < BUF_SIZE ) {
		
		perror("Ocurrió un error al enviar mensaje al sistema");
		ret=" ";
		sprintf(ret, "%c", MSJ_ERROR);
}
	else {
		if ( (accion == ACT_LISTA) || (accion == ACT_EST) ) {
			
			if ( (read(socket, msj, BUF_SIZE)) < BUF_SIZE ) {   //Espero la respuesta (sin importar bloqueo ya que quiero la respuesta del sist.)
			
				perror("Ocurrió un error al leer mensaje del sistema");

				ret=" ";
				sprintf(ret, "%c", MSJ_ERROR);
				
			}
			else {

				ret = msj;
			}
			
		}
		else {
			
			ret=" ";
			sprintf(ret, "%c", MSJ_ENVIADO);
		}
	}
	
	return ret;
}	


