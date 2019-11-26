#include "SocketFunc.h"

int sockEscuchar(uint16_t puerto){
	
	struct sockaddr_in structSock;
	
	//Creo socket:
	int sockId = socket (PF_INET, SOCK_STREAM, 0); //Socket IDS, comm: TCP

	if (sockId < 0) {
		sockId = SOCKET_ERROR;
	}
	else {
		//Configuro socket de escucha:
		if (configurarSocketL(sockId, structSock, puerto) == EXIT_FAILURE) {
				sockId = SOCKET_ERROR;
		}
	}
	
	return sockId;	
	
}

int configurarSocketL(int sockId, struct sockaddr_in structSock, uint16_t puerto){
	
	int ret=EXIT_SUCCESS;
	
	//Se pudo crear socket, entonces ingreso datos:
	structSock.sin_family = AF_INET;
	structSock.sin_port = htons (puerto);
	structSock.sin_addr.s_addr = htonl ( INADDR_ANY ); //Enlaza el socket a toda interface disp.
	
	//Hago enlace:
	if (bind (sockId, (struct sockaddr *) &structSock, sizeof (structSock)) < 0) {
	
		ret = EXIT_FAILURE;
	}

	else {		
	
		// Lo pongo a escuchar para aceptar conexiones:
		if (listen (sockId, MAX_CLIENTS) < 0) {
		
			ret = EXIT_FAILURE;
		}
	}		
	
	return ret;	
}

int sockAceptar (int sockId) {

	//Aceptar conexion
	struct sockaddr addr;
	socklen_t largo = sizeof(struct sockaddr);

	int rdsocket;
	
	if ( (rdsocket = accept(sockId, &addr, &largo)) < 0 ) {
	
		rdsocket = -1;
	}

	return rdsocket;
}

int sockConectar (char* dir, uint16_t port) {

	int sockId;
	struct sockaddr_in serverSock;

	//Creo Socket
	sockId = socket (PF_INET, SOCK_STREAM, 0);
	if (sockId > 0) {
	
		//Asigno datos a Socket
		serverSock.sin_family = AF_INET;
		serverSock.sin_port = htons (port);
		if (dir == NULL) {
			serverSock.sin_addr.s_addr = htonl ( INADDR_LOOPBACK );
		} else {
			if (inet_aton(dir, &serverSock.sin_addr) == 0) {
				sockId = SOCKET_ERROR;
			}
		}

		//Conecto
		if (connect (sockId, (struct sockaddr *) &serverSock, sizeof(serverSock)) == -1) {
			sockId = SOCKET_ERROR;
		}

	}
	return sockId;
}


char *selectSockets (int myreadfds[], int mywritefds[], int myexceptfd, long time_out, char *buffer[], int newSockRead, char (*actLectura)(char *), char (*actEscritura)(char *)) {
	
	char *ret = ""; //Retorna los nuevos socketsfds de !!
	

	int i, newSock, maxfd = 0, s = -1; //Tomo s = -10 para ver si
	int nr = sizeof( &myreadfds ) 	/ sizeof( myreadfds[0] );
	int nw = sizeof( &mywritefds ) 	/ sizeof( mywritefds[0] );
	fd_set readfds, writefds, exceptfd;
	struct timeval timeout;

	// Limpiar los conjuntos
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_ZERO(&exceptfd);

	// Cargar los fd_set (y además reajustar nr y nw)
	int resto = 0;
	for ( i = 0; i < nr; i++) {

		//Como puedo tener ceros, asigno solo los socket > 0
		if( myreadfds[i] > 0 ) { 
			FD_SET(myreadfds[i], &readfds);
		}
		else resto++;
		

	}
	nr = nr - resto;	

	resto = 0;
	for ( i = 0; i < nw; i++) {

		if( mywritefds[i] > 0 ) { 
			FD_SET(mywritefds[i], &writefds);
		}
		else resto++;
		
	}

	nw = nw - resto;	
	
	//Seteo posible socket de escucha
	if (myexceptfd > 0) {
		FD_SET(myexceptfd, &exceptfd);
	}
	
	// Cargar el timeout
	timeout.tv_sec = time_out;
	timeout.tv_usec = 0;

	// Enccontrar el mayor filedescriptor DE TODOS
	for ( i = 0; i < nr; i++) {
		maxfd = maxfd < myreadfds[i] ? myreadfds[i] : maxfd;
	}

	for ( i = 0; i < nw; i++) {
		maxfd = maxfd < mywritefds[i] ? mywritefds[i] : maxfd;
	}

	maxfd = maxfd < myexceptfd ? myexceptfd : maxfd;
	


	// EJECUTO SELECT
	while ( (s = select(maxfd + 1, &readfds, &writefds, &exceptfd, &timeout)) >= 0) {

		if (s > 0) {
		
			// reviso los filedescriptors de lectura
			for ( i = 0; i < nr; i++) {

				if (FD_ISSET(myreadfds[i], &readfds)) {

						read (myreadfds[i], buffer[i], BUF_SIZE);
						actLectura(buffer[i]);
						

				} else {
						FD_SET(myreadfds[i], &readfds);

				}
			}
			// reviso los filedescriptors de escritura
			for ( i = 0; i < nw; i++) {

				if (FD_ISSET(mywritefds[i], &writefds)) {

						write (mywritefds[i], buffer[i], BUF_SIZE);
						actEscritura(buffer[i]);

				} else {
						FD_SET(mywritefds[i], &writefds);

				}
			}
			// reviso el filedescriptor de excepcion(escucha)

			if (FD_ISSET(myexceptfd, &exceptfd)) {

				newSock = sockAceptar(myexceptfd);
						
				//Evaluo segun newSockRead dado por proc. si es read o write
				char *add = "";						

				if( newSockRead ) {

					sprintf(add, "%d,r\n", newSock);
					sprintf(ret,"%s-%s", ret, add);
				}

				else {

					sprintf(add, "%d,w\n", newSock);
					sprintf(ret,"%s-%s", ret, add);
				}
													
			} 
				
			else {
				FD_SET(myexceptfd, &exceptfd);
			}

			

		}

	}
	
	return ret;

}
