#ifndef _AFUN_H_
#define _AFUN_H_

#include "../Sockets/SocketFunc.h"
#include "../SHM/SHMFun.h"
#include "../GeneralFunctions.h"
#include "../DynamicLists.h"

#define ERROR_EST -1

//Funciones de lectura y accion en listas/estados/acciones
char *leerDatos (char *buf, void *shm);
int setEstado(int pid, int estado, Proceso *shm, sem_t *sem);
int getEstado (int pid, Proceso *shm, sem_t *sem); 
int devolverMsj (char *buf);
char *generarLista(int filtro, int socket, Proceso *shm, sem_t *sem);
Proceso *getUbicacionLibre(Proceso *shm, sem_t *sem);
void crearProcSHM (int pid, int estado, char *data, int socket, Proceso *ubicacionLibre, sem_t *sem);

#endif
