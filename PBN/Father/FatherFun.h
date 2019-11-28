#ifndef _FATHERFUN_H_
#define _FATHERFUN_H_

#include "../SHM/SHMFun.h"
#include <time.h>

//Macros
#define DIR_R "../Receptor/R"
#define DIR_PM "../ProcessManager/PM"
#define DIR_L "../Listener/L"
#define DIR_A "../Actuador/A"
#define TIME 3

//Firmas
int *crearProcSis(int puerto);

void eliminarSistema(int *pid, int id, void *shm, sem_t *sem);

void signal_handler(int signal);

void cargarListaVacia(Proceso *pros, sem_t *sem);

#endif
