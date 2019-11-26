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

//-Acciones:
#define ACT_CREAR 0
#define ACT_BORRAR 1
#define ACT_SUSP 2
#define ACT_REAN 3
#define ACT_ENGAN 4
#define ACT_LISTA 5
#define ACT_EST 6

//-Filtros:
#define FILTRO_ALL 0
#define FILTRO_SP 1
#define FILTRO_SUSP 2
#define FILTRO_ACT 3 //(Activos o en ejec.)
#define FILTRO_EST 4
#define ERROR_PID -1 //Para cuando la lista sea nula y no pueda elegir PID

#define MSJ_ENVIADO 'E'
#define MSJ_ERROR 'F'


//Firmas:
int conectarSist(int *dir, int timeOut); 		//Direccion: ip:puerto ej:192.168.0.1:8000
//***func. para manejo de Interrupciones-Señales
char *enviarAccion(int accion, int datoNum, char *datos, int socket); 	//Devuelve mensaje correspondiente a la accion o error.  **Revisar si es necesario accion y datos
void cerrarSistema(void);


#endif
