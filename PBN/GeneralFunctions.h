#ifndef _GENERALFUNCTIONS_H_
#define _GENERALFUNCTIONS_H_


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/errno.h>
#include <signal.h>
//#include <error.h>

typedef struct proceso {
    pid_t pid;
    char data[255];   //Largo maximo del nombre es 255 en Unix (dir + parametros!!)
    int estado;         // Ej. ejecutar
    char *creador;
} Proceso;

//Macros

//Macros de estados de procesos:
#define PARA_EJECUTAR 0
#define ELIMINAR 1
#define SUSPENDIDO 2
#define REANUDAR 3
#define ACTIVO 4

//Firmas
int ejecProceso(char *dir, char *arg[]);

//Proceso crearProceso(char *direccion,char *creador);

#endif