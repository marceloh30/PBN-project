#ifndef _COMCONSOLA_H_
#define _COMCONSOLA_H_
	
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <time.h>
#include "../Sockets/SocketFunc.h"

//Macros:
#define Errmsj(estado,text) error_at_line(estado, errno, __FILE__, __LINE__, text)

#define ERROR_PID -1 

#define MSJ_ENVIADO 'E'
#define MSJ_ERROR 'F'


//Firmas:
int conectarSist(int *dir, int timeOut); 		//Direccion: ip:puerto ej:192.168.0.1:8000
//***func. para manejo de Interrupciones-Señales
char *enviarAccion(int accion, int datoNum, char *datos, int socket); 	//Devuelve mensaje correspondiente a la accion o error.  **Revisar si es necesario accion y datos
void cerrarSistema(void);


#endif
