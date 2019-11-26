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
int opcion(int valorInf, int valorSup, int *exceps); 		//Devuelve num. entre valores esperados
int condExcepciones(int ingreso, int *exceps, int largoEcp);//Complementa opcion() buscando evitar numeros que no esten en una lista
int seleccionProceso (int filtro, int socket);					//Devuelve PID si es ingreso correcto. 

void getLimites (char *lista, int limites[]);								//Obtiene limites superior e inferior para una lista.
int *getExcepLista (char *lista);							//Consigue PIDs faltantes en una lista de procesos
char *devolverLista(char *datos);							//Recibe datos de una lista y genera y devuelve otra amigable al usuario

#endif
