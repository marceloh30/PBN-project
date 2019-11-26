#ifndef _SHMFUN_H_
#define _SHMFUN_H_

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <errno.h>

//Macros

#define SHM_FAIL -1
#define SHM_ID 1234
#define SHM_SIZE 2048

//Firmas
int desconectarSHM(char *path);

int eliminarSHM(char *path);

void *conectarSHM(char *path);

int generarID(char *path);

void *crearSHM(char *path);

#endif