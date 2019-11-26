#include "ConsolaFun.h"

//Eleccion de Opcion

int opcion(int valorInf, int valorSup, int *exceps){
	int ingreso,largoEcp;
	if(exceps == 0){
		largoEcp = 0;
	}
	else{
	largoEcp = sizeof(exceps) / sizeof(exceps[0]);
	}
		printf("\nIngrese opcion: ");
	while( ! (scanf("%d",&ingreso) && ingreso >= valorInf && ingreso <= valorSup && (!largoEcp || condExcepciones(ingreso,exceps,largoEcp) )) ){
		scanf("%*[^\n]"); //Limpio buffer
		printf("\nIngreso incorrecto.\nPor favor, ingrese un valor de la lista: ");
	}	
	
			
	return ingreso;
}
////


//Excepciones de una lista: condExcepciones()

int condExcepciones(int ingreso, int *exceps, int largoEcp) {
	int ret=1;
	int i;
	for(i=0; i<=largoEcp; i++){
		if (ingreso == exceps[i]) ret=0; //Si el ingreso coincide con alguna exc., devuelvo "false"(cero)
	}
	return ret;
}
////


//Seleccion de proceso de una lista:

int seleccionProceso ( int filtro, int socket ) {
	
	printf("Accediendo a datos del sistema...\n\n");
	
       	char *lectura = enviarAccion(ACT_LISTA, filtro, "", socket);

	int pidSeleccionado;
	
	if (lectura[0] != MSJ_ERROR) {
		
		int limites[] = { 0 , 0 };
		getLimites (lectura, limites);	//Cargo los valores correctos del array
		int excep[] = {0};	

		char *lista = devolverLista( lectura ); 

		pidSeleccionado = ERROR_PID;
		
		if ( !(lista && lista[0]) ) {
			
			printf("Elija un PID de la lista :\n%s", lista);

			pidSeleccionado = opcion(limites[0], limites[1], excep);		
		}
		
	}
	else {
		
		pidSeleccionado = ERROR_PID;	
	}

	return pidSeleccionado;
}
////


//Obtener numeros faltantes en una lista: getExcepLista()

int *getExcepLista(char *lista) {
	
	int excepciones[100];

	int prev = atoi(lista); //Obtengo el primer valor de la lista
	
	while(){	
	
	
	return lista; 
}
////


//Obtener limites de eleccion de una lista para el usuario: getLimites()
void getLimites(char lista[], int limites[]) {

	char c;
	int max = 0;
	int min = 101; //Minimo es mayor a la maxima cantidad de procesos (entonces es como decir de la lista)
    
    	int i, dig, num = 0;

	for ( i=0; i <= strlen(lista); i++ ) {

    		c = lista[i];

		if ( isdigit(c) ) {

			dig = atoi(&c);
			num = num*10 + dig;
		}	
		else { 
	
			if ( (num != 0) && (max < num) ) {
					
				max = num;
			}
			if ( (num != 0) && (min > num) ) {

				min = num;
			}
			num = 0;	
		}
    		
	}

	limites[0] = min ;
	limites[1] = max ; //Guardo en array minimo y maximo.
		
}
////	
	
	
	

//Devolucion de lista amigable al usuario: devolverLista()

char *devolverLista(char *datos){
	//char ret[BUF_SIZE];
	//char *str1, *str2;

	//Realizo primer strtok y luego itero:
	

		
	
	
	return datos;
}
////
