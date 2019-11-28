#include "FunMenus.h" 
int contectado;
//Menu inicial:
void menuInicial(void) {
	conectado = 0;
	int socket;
	
	int opc = -1;
	while(opc != 2) {
		
		printf(STR_MI);
		opc = opcion(1, 2, NULL);
		while ((opc = opcion(1, 2, 0, 0)) == ERROR_RD ); 
		
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

				else if ( ip[0] < 0 || ip[0] > 255 || ip[1] < 0 || ip[1] > 255 || ip[2] < 0 || ip[2] > 255 || ip[3] < 0 || ip[3] > 255 || ip[4] < 1024 || ip[4] > 65535 ) {
					
					ingrCorrecto = 0;
					printf("\n\nIngresa una ip correcta!\n");
				} 

			 	else ingrCorrecto = 1;
				
			} while(!ingrCorrecto);
			 
			if ( ( socket = conectarSist(ip,TIME_OUT) ) > 0 ) {
				conectado = 1;
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

				if(res==1) {
					Errmsj(EXIT_SUCCESS, "Adios! (Saliste del Menu inicial)\n");		
				}
				else opc=-1;
			}	

		}

	}
}
////

//Menu principal:

void menuPrincipal( int socket ) {
	char buffer[BUF_SIZE];

	int opc = -1;
	while ( opc != 6 && opc != 7 && conectado) {
	
		printf(STR_MP);

		while ((opc = opcion(1, 7, 1, socket)) == ERROR_RD ); //Pido hasta que el ingreso sea correcto.

		switch	( opc ) {

			case 1: { //Submenu crear / borrar
				Submenu1( socket );
				break;
			}
			case 2: { //Submenu susp / rean
				Submenu2( socket );
				break;
			}
			case 3: { //Pedir Estado de un proceso

				int procesoElegido = seleccionProceso(FILTRO_ALL, socket, buffer);
				enviarAccion ( ACT_EST, procesoElegido, "" , socket);			
				break;
			}
			case 4: { //Lista proc. S/P

				devolverLista ( enviarAccion ( ACT_LISTA, FILTRO_SP , "" , socket), FILTRO_SP ); //Bloquea esperando respuesta!!
				break;
			}
			case 5: { //Engancharse a salida de proceso
			
				int procesoElegido = seleccionProceso(FILTRO_ALL, socket, buffer);
				enviarAccion ( ACT_ENGAN, procesoElegido, "" , socket);	
				break;

			}
			case 6: { //Cerrar sesion
				close(socket); //Cierro mi conexion con el socket.
				break;
			}
			case 7: { //Cerrar sistema
				enviarAccion ( ACT_CERR_SIST, 0 , "" , socket);
				close(socket);
				break;
			}
			default: printf("\nError de ingreso:\nElija una opcion entre 1 y 7\n");
		
		}
	}

}
////

//Submenu1:

void Submenu1( int socket ) {
	
	char buffer[BUF_SIZE];

	printf(STR_SM1);
	int opc=-1;
	while(opc != 3) {
		
		while ((opc = opcion(1, 3, 1, socket)) == ERROR_RD ); //Pido hasta que el ingreso sea correcto.
		
		switch(opc) {
			case 1: {
				int r;
				size_t size = BUF_SIZE;
				char *procSt = (char *) malloc (size);
				do {
				printf ("Ingrese proceso a crear: ");

				r = getline (&procSt, &size, stdin);
				} while (r == -1);

				enviarAccion ( ACT_CREAR, 0 , procSt , socket);		
				free(procSt);
				break;
			}
			case 2: {

				int pid = seleccionProceso(FILTRO_ALL, socket);					
				enviarAccion ( ACT_BORRAR, pid, "" , socket);			
				break;
			}
			case 3: {
				break; //Volver al MP
			}
			default: printf("\nError de ingreso.\nElija una opcion entre 1 y 3\n");
			
		}
		
	}
}
////

//Submenu2:

void Submenu2( int socket ) {
	
	char buffer[BUF_SIZE];

	printf(STR_SM2);
	int opc=-1;
	while(opc != 3) {		
	
	
		while ((opc = opcion(1, 3, 1, socket)) == ERROR_RD ); //Pido hasta que el ingreso sea correcto.
		
		switch(opc) {
			case 1: {
				
				int pid = seleccionProceso(FILTRO_ACT, socket);					
				enviarAccion ( ACT_SUSP, pid, "" , socket);			
				break;
			}
			case 2: {
				
				int pid = seleccionProceso(FILTRO_SUSP, socket);					
				enviarAccion ( ACT_REAN, pid, "" , socket);			
				break;
			}
			case 3: {
				break; //Volver al MP
			}
			default: printf("\nError de ingreso:\nElija una opcion entre 1 y 3\n");
			
		}
		
	}
}
////
