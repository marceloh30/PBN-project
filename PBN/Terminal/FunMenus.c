#include "FunMenus.h" 

//Menu principal:

void menuPrincipal( int socket ) {
	int opc = -1;
	while ( opc != 6 && opc != 7 ) {
	
		printf(STR_MP);

		opc = opcion(1,7);
		
		//selectSockets ( stdin, socket, int myexceptfd, long t_out, char *buff[], char *(*actRd)(char *, void *), void *shm, int (*actWr)(char *))

		switch	( opc ) {

			case 1: {
				Submenu1( socket );
				break;
			}
			case 2: {
				Submenu2( socket );
				break;
			}
			case 3: {

				int procesoElegido = seleccionProceso(FILTRO_ALL, socket);
				enviarAccion ( ACT_EST, procesoElegido, "" , socket);			
				break;
			}
			case 4: {

				devolverLista ( enviarAccion ( ACT_LISTA, FILTRO_SP , "" , socket), FILTRO_SP );
				break;
			}
			case 5: {

				seleccionProceso(FILTRO_ALL, socket);				
				break;

			}
			case 6: {
				close(socket); //Cierro mi conexion con el socket.
				break;
			}
			case 7: {
				enviarAccion ( ACT_CERRAR_SIST, 0 , "" , socket);
				close(socket);
				break;
			}
			default: printf("\nError de ingreso:\nElija una opcion entre 1 y 7\n");
		
		}
	}

}
////

//Menu inicial:

void menuInicial(void){

	int socket;
	
	int opc = -1;
	while(opc != 2){
		
		printf(STR_MI);
		opc = opcion(1,2);
		
		
		if (opc == 1) {
			
			int ingrCorrecto;
			int ip[5];
			char buffer[1024]; //Asigno buffer para eliminar caracteres erroneos.
			do{

				if(!fgets(buffer, 1024, stdin)){
					printf("Ingrese correctamente el dato.\n");
				}	

				printf("\nIngrese IP y puerto (Formato: xxx.xxx.xxx.xxx:xxxxx): ");
				
				if( scanf("%d.%d.%d.%d:%d", &ip[0] ,&ip[1] ,&ip[2] ,&ip[3] ,&ip[4]) != 5 ){ //Puedo usar strtok para separar (ver foto) y verificar mejor
					
					ingrCorrecto = 0;
					printf("No te olvides de ingresar correctamente el formato!!\n\n");
				}

				else if ( ip[0]<0 || ip[0]>255 || ip[1]<0 || ip[1]>255 || ip[2]<0 || ip[2]>255 || ip[3]<0 || ip[3]>255 || ip[4]<1024 || ip[4]>65535 ) {
					
					ingrCorrecto = 0;
					printf("\n\nIngresa una ip correcta!\nip: %d.%d.%d.%d:%d\n", ip[0], ip[1], ip[2], ip[3], ip[4]);
				} 

			 	else ingrCorrecto = 1;
				
			} while(!ingrCorrecto);
			 
			if ( ( socket = conectarSist(ip,TIME_OUT) ) > 0 ) {
				
				menuPrincipal(socket);
			}

			else {
				printf("Ocurrió un error al conectar al sistema!!\n Intente otra vez.\n\n");
				perror("Error");
			}

		}

		else if	(opc == 2) {
			int res;
			printf("Esta seguro que desea salir?\n Si así lo desea ingrese '1'\nIngreso: ");
			if ( scanf ( "%d", &res ) ){
				scanf("%*[^\n]"); //Limpio buffer

				if(res==1){
					Errmsj(EXIT_SUCCESS, "Adios! (Saliste del Menu inicial)\n");		
				}

				else opc=-1;
			}	

		}

	}
}
////

//Submenu1:

void Submenu1( int socket ){
	
	printf(STR_SM1);
	int opc=-1;
	while(opc != 3){		
	
		opc = opcion(1,3);
		
		switch(opc){
			case 1:{
				
				//crearProceso();
				
				break;
			}
			case 2:{
				
				//borrarProceso();
				
				break;
			}
			case 3:{
				break; //Volver al MP
			}
			default: printf("\nError de ingreso.\nElija una opcion entre 1 y 3\n");
			
		}
		
	}
}
////

//Submenu2:

void Submenu2( int socket ){
	
	printf(STR_SM2);
	int opc=-1;
	while(opc != 3){		
	
		opc = opcion(1,3);
		
		switch(opc){
			case 1:{
				
				//suspenderProceso();				
				break;
			}
			case 2:{
				
				//reanudarProceso();				
				break;
			}
			case 3:{
				break; //Volver al MP
			}
			default: printf("\nError de ingreso:\nElija una opcion entre 1 y 3\n");
			
		}
		
	}
}
////
