#ifndef _CONSOLAFUN_H_
#define _CONSOLAFUN_H_

#include "ComConsola.h"
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>


//Firmas:
int opcion(int valorInf, int valorSup); 		//Devuelve num. entre valores esperados
int opcionPID(int *pids);				//Devuelve pid entre pids esperados
int *getPIDS(char *datos);
int seleccionProceso (int filtro, int socket);		//Devuelve PID si es ingreso correcto. 
char *devolverLista(char *datos, int filtro);			//Recibe datos de una lista y genera y devuelve otra amigable al usuario

#endif
