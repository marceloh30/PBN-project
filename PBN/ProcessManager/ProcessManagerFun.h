#ifndef _PROCESSMANAGER_H
#define _PROCESSMANAGER_H

#include "../GeneralFunctions.h"
#include "../SHM/SHMFun.h"
#include "../Sockets/SocketsFunc.h"
#include <setjmp.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

//Macros:
#define TIEMPO_SEC 10
#define TIEMPO_MILISEC 0
#define FINALIZO -1
#define NO_CREADO -2
#define CREADO -3

int reanudarProceso(pid_t pid);

int suspenderProceso(pid_t pid);

int accionATomar(Proceso *direc, sem_t *sem);

int ejecutar(pid_t pid);

void eliminarProcesos(Proceso *lista);

#endif
