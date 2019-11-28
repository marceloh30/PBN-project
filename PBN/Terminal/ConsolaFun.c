#include "ConsolaFun.h"



//Funciones para select:
char *rd(char *buf, void *rdsocks, int socket) {
	
	if (socket != STDIN_FILENO) { //Si es stdin, retorna el buffer recibido, en otro caso tomo accion.
		
		int result = atoi(strtok_r(bufTmp, ",", &saveptr));		
		if (result == WRITE_SOCK) {
			
			int caso = atoi(strtok_r(NULL, ",", &saveptr));
			switch (caso) {
				//Los casos de lectura al pedir lista y pedir estado se encuentran en 
				//ComConsola.c --> enviarAccion
				case (ACT_REAN | ACT_SUSP | ACT_BORRAR): {
					int datoNum = atoi(strtok_r(NULL, ",", &saveptr));
					
					if (caso == ACT_REAN) { 
					
						fprintf (stderr, "[%d] Proceso Reanudado.\n", datoNum);		
					}
					else {
						(caso == ACT_SUSP) ? fprintf(stderr, "[%d] Proceso Suspendido.\n", datoNum) : fprintf(stderr, "[%d] Proceso Eliminado.\n", datoNum);
					}
					break;
				}
				
				default: break;
			}
		}
		else fprintf(stderr,"Error interno del sistema: %s\n",buf); //Algun error interno
	}
	return buf;
}

int actWr(char *buf, int socket) {
	int ret = 0;
	
	(socket == STDIN_FILENO) ? ret = 0 : ret = 1; //Escribo solo hacia el socket de Rp.
	
	return ret;
}

//Eleccion de Opcion
int opcion(int valorInf, int valorSup, int doSelect, int socket) {
	
	int ingreso;
	
	//variables para select:
	static char bufStdin [BUF_SIZE];
	static char bufRp [BUF_SIZE];
	static char *bufs[2] = {bufStdin, bufRp};
	int rdSocks[2] = {STDIN_FILENO, socket};
	int wrSock[2] = {socket, 0}; //Dejo igual cantidad por compatibilidad de selectSockets
	
	printf("\nIngrese opcion: ");

	if (doSelect) { //Ya pase el menu de conexion: Tengo socket con mi Rp
		void *rdsocksVoid = (void *) rdSocks;
		selectSockets (rdSocks, wrSock, 0, 0, bufs, rd, rdsocksVoid, actWr); //No tiene timeout!
		
		if( ! ( sscanf(buffer, "%d", &ingreso) && ingreso >= valorInf && ingreso <= valorSup ) ) {
			
			sscanf(buffer, "%*[^\n]"); //Limpio buffer
			ingreso = ERROR_RD;
			printf("\nIngreso incorrecto.\nPor favor, ingrese un valor de la lista: ");

		}
		
	}
	else { //Estoy en menu de conexion.
		
		if( ! ( scanf("%d", &ingreso) && ingreso >= valorInf && ingreso <= valorSup ) ) {
			
			scanf("%*[^\n]"); //Limpio buffer
			ingreso = ERROR_RD;
			printf("\nIngreso incorrecto.\nPor favor, ingrese un valor de la lista: ");

		}	
	}	
		return ingreso;		
		
	}
	
}
////

//Eleccion de pids de la lista
int opcionPID (int *pids, int socket) {

	int ingreso, largoPids, i;
	int ingresoCorrecto = 0;
	static char *buff;
	
	if(pids == 0) {
		largoPids = 0;
	}
	else {
	largoPids = sizeof(pids) / sizeof(pids[0]);
	}

	printf("\nIngrese PID: ");

	while( ! ( sscanf(buff, "%d", &ingreso) && !ingresoCorrecto ) ) {

		sscanf(buff, "%*[^\n]"); //Limpio buffer		

		for(i = 0; i < largoPids; i++) {

			ingresoCorrecto = ingreso == pids[i] ? 1 : 0;
		}

	 	!ingresoCorrecto ? printf("\nIngreso incorrecto.\nPor favor, ingrese un valor de la lista: ") : printf("Ingreso correcto. \n");		
	}	
	
			
	return ingreso;
}
////


//Obtener pids para opcionPID()
int *getPids (char *lista) {
	static int pidBuf[CANT_PROC];
	static int *pids = pidBuf;
	char c;
    
    int i, dig, num = 0, j = 0;

	for ( i=0; i <= strlen(lista); i++ ) {

    		c = lista[i];

		if ( isdigit(c) ) {

			dig = atoi(&c);
			num = num*10 + dig;
		}	
		else if (j <= 100) { 
	
			pids[j] = num;
			j++;
			num = 0;	
		}
    		
	}

return pids;
}
////	
	

//Seleccion de proceso de una lista:

int seleccionProceso (int filtro, int socket) {
	
	printf("Accediendo a datos del sistema...\n\n");
	
    static char *lectura = enviarAccion(ACT_LISTA, filtro, "", socket);

	int pidSeleccionado;
	
	if (lectura[0] != MSJ_ERROR) {
		
		char *lista = devolverLista( lectura, filtro ); 

		pidSeleccionado = ERROR_PID;
		
		if ( !(lista && lista[0]) ) {
			
			printf("Elija un PID de la lista :\n%s", lista);

			pidSeleccionado = opcionPID ( getPids(lectura), socket );		
		}
		
	}
	else {
		
		pidSeleccionado = ERROR_PID;	
	}

	return pidSeleccionado;
}
////



	
	

//Devolucion de lista amigable al usuario: devolverLista()

char *devolverLista (char *datos, int filtro) {
	
	static char ret[BUF_SIZE];
	char dataTmp[BUF_SIZE];
	strcpy(dataTmp,datos); //Paso a array de char para funcionamiento correcto de strtok()
	
	int num, verif = 0;
	
	char *saveptr1;
	char *res;
	
	switch (filtro) {

		case FILTRO_ALL | FILTRO_SUSP | FILTRO_ACT: {

			sprintf(ret, "\nLista de PIDs:\n");

			while  ( NULL != (res = ( strtok_r((verif ? NULL : dataTmp ),",",&saveptr1) ) ) )   {
				verif = 1;
				
				num = atoi(res);
				sprintf(ret, "%s-[%d]\n", ret, num);
			}	
			break;
		}

		case FILTRO_SP: { 

			char *chr, *saveptr2;
			
			sprintf(ret, "\nLista de PIDs segun sesion/planificador:\n");

			while  ( NULL != (res = ( strtok_r( (verif ? NULL : dataTmp ),",",&saveptr1) ) ) )   {
				verif = 1;

				chr = strtok_r(res,"-",&saveptr2);

				num = atoi(strtok_r(NULL,"-",&saveptr2));

				if(chr[0] == 's'){
					sprintf(ret, "%s[%d] - Sesion\n", ret, num);
				}
				else {

					sprintf(ret, "%s[%d] - Planificador\n", ret, num);

				}

			}
			sprintf(ret, "%s\n", ret);
			break;
		}
	

		
		default: {

			perror("Error de filtro");
			break;
		}
	}
	
	static char *retorno = ret;
	return retorno;

}
////
