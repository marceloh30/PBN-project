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
    int creadorSock; //Socket para identificar creador.
} Proceso;

//Macros

#define SHM_PATH "../SHM/keyGeneratorSHM"

#define SHM_FAIL -1
#define SHM_ID 1234
#define SHM_SIZE 27000 //Cada proceso ocupa 268bytes x 100 = 26,8kB, le agrego 200 para semaforo y extras.

//Firmas
int desconectarSHM(void *shmp);

int eliminarSHM(int ID);

void *conectarSHM(char *path);

int generarID(char *path);

void *crearSHM(char *path);

char *crearArray(Proceso unProceso);

Proceso crearEstructura(char *proArray);
