#ifndef _GENERALFUNCTIONS_H_
#define _GENERALFUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/errno.h>
#include <signal.h>
//#include <error.h>

//Macros

//Macros de estados de procesos:
#define NUEVO 0
#define ELIMINAR 1
#define SUSPENDIDO 2
#define REANUDAR 3
#define ACTIVO 4
#define SUSPENDER 5
#define EN_EJECUCION 6
#define ELIMINADO 7

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

//Firmas
int ejecProceso(char *dir, char *arg[]);

#endif

