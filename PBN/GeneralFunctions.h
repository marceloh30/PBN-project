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

//Firmas
int ejecProceso(char *dir, char *arg[]);

