#ifndef _SHMFUN_H_
#define _SHMFUN_H_

#include "../Semaforo/Semaforo.h"
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

typedef struct Proceso {
    pid_t pid;
    char *data;   //Largo maximo del nombre es 255 en Unix (dir + parametros!!)
    int estado;   // Ej. ejecutar
    int sockCreador;
} Proceso;

//Macros

#define DIR_KEY_SHM "../SHM/keyGeneratorSHM"

#define SHM_FAIL -1
#define SHM_ID 1234
#define SHM_SIZE 20000 //20kB para ocupar 100 procesos (de 267 bytes cada uno) y tener ademas bytes libres

#define PROC_OFFSET 50   //Punto del cual comienza la lista de procesos

//Firmas
int desconectarSHM(void *shmp);

int eliminarSHM(int ID);

void *conectarSHM(char *path);

int generarID(char *path);

void *crearSHM(char *path);

char *crearArray(Proceso unProceso);

Proceso crearEstructura(char *proArray);

Proceso tomarProcSHM(Proceso *lista, sem_t *sem);

void guardarProcSHM(Proceso proc, Proceso *lista, sem_t *sem);

#endif
