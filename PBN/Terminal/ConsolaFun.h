#ifndef _CONSOLAFUN_H_
#define _CONSOLAFUN_H_

#include "ComConsola.h"
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#define ERROR_RD -1

//Firmas:

//Para select:
char *rd(char *buf, void *ptr, int socket);
int actWr(char *buf, int socket);
//Para pedir opciones:
int opcion(int valorInf, int valorSup, int doSelect, int socket); 		//Devuelve num. entre valores esperados y hace select stdin/socket si se precisa
int opcionPID(int *pids, int socket);									//Devuelve pid entre pids esperados y luego igual que opcion.
int seleccionProceso (int filtro, int socket);				//Devuelve PID si es ingreso correcto.  
//Devolver listas:
int *getPIDS(char *datos);
char *devolverLista(char *datos, int filtro);			//Recibe datos de una lista y genera y devuelve otra amigable al usuario

#endif
