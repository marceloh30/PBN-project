#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

typedef struct proceso {
    pid_t pid;
    char *data;   //Largo maximo del nombre es 255 en Unix (dir + parametros!!)
    int estado;   // Ej. ejecutar
    int sockCreador;
} Proceso;

//Macros

#define SHM_PATH "../SHM/keyGeneratorSHM"

#define SHM_FAIL -1
#define SHM_ID 1234
#define SHM_SIZE 20000 //20kB para ocupar 100 procesos (de 267 bytes cada uno) y tener ademas bytes libres

//Firmas
int desconectarSHM(void *shmp);

int eliminarSHM(int ID);

void *conectarSHM(char *path);

int generarID(char *path);

void *crearSHM(char *path);

char *crearArray(Proceso unProceso);

Proceso crearEstructura(char *proArray);
