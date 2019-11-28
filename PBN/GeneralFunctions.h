#ifndef _GENERALFUNCTIONS_H_
#define _GENERALFUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/errno.h>

//Macros
#define WRITE_SOCK 1
#define CANT_PROC 100
#define MAX_CLIENTS 8 //Maxima cantidad de clientes en el sistema

//Macros de estados de procesos:
#define NUEVO 0
#define ELIMINAR 1
#define SUSPENDIDO 2
#define ACTIVO 3
#define EN_EJECUCION 4
#define ELIMINADO 5

//-Acciones:
#define ACT_CREAR 0
#define ACT_BORRAR 1
#define ACT_SUSP 2
#define ACT_REAN 3
#define ACT_ENGAN 4
#define ACT_LISTA 5
#define ACT_EST 6
#define ACT_CERR_SIST 7 

//-Filtros:
#define FILTRO_ALL 0
#define FILTRO_SP 1
#define FILTRO_SUSP 2
#define FILTRO_ACT 3 //(Activos o en ejec.)
#define FILTRO_EST 4

//-Errores:
#define ERROR_PID -1 //Para cuando la lista sea nula y no pueda elegir PID
#define ERROR_PRC -2 //Errores de por ejemplo: crear proceso
#define ERROR_SHM -3 //Errores dados por algo de SHM: p. ej: falta de espacio.
#define ERROR_PM -4
#define ERROR_A -5
#define ERROR_ACT -6


//Firmas
int ejecProceso(char *dir, char *arg[]);

#endif

