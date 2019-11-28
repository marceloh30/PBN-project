#include "ConsolaFun.h"

//Eleccion de Opcion
int opcion(int valorInf, int valorSup){
	int ingreso;

	printf("\nIngrese opcion: ");

	while( ! ( scanf("%d",&ingreso) && ingreso >= valorInf && ingreso <= valorSup ) ) {

		scanf("%*[^\n]"); //Limpio buffer
		printf("\nIngreso incorrecto.\nPor favor, ingrese un valor de la lista: ");

	}			
	return ingreso;
}
////

//Eleccion de pids de la lista
int opcionPID (int *pids) {

	int ingreso, largoPids, i;
	int ingresoCorrecto = 0;

	if(pids == 0) {
		largoPids = 0;
	}
	else {
	largoPids = sizeof(pids) / sizeof(pids[0]);
	}

	printf("\nIngrese PID: ");

	while( ! ( scanf("%d", &ingreso) && !ingresoCorrecto ) ) {

		scanf("%*[^\n]"); //Limpio buffer		

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
	int pidBuf[CANT_PROC];
	int *pids = pidBuf;
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
	
       	char *lectura = enviarAccion(ACT_LISTA, filtro, "", socket);

	int pidSeleccionado;
	
	if (lectura[0] != MSJ_ERROR) {
		
		char *lista = devolverLista( lectura, filtro ); 

		pidSeleccionado = ERROR_PID;
		
		if ( !(lista && lista[0]) ) {
			
			printf("Elija un PID de la lista :\n%s", lista);

			pidSeleccionado = opcionPID ( getPids(lectura) );		
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
	
	char ret[BUF_SIZE];
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
	
	char *retorno = ret;
	return retorno;

}
////
