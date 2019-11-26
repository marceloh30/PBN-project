//incluir senales!!!
#include "../GeneralFunctions.h"
#include <setjmp.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

//Macros:
#define TIEMPO_SEC 50
#define TIEMPO_MILISEC 0

//Firmas:
//int accionSHM(short int pidProceso, char *data); //Devuelve pid del proceso al cual realizó una accion
//
//void analizarSHM(void); //Es el encargado de llamar a accionSHM() y mirar proceso por proceso en SHM para realizar acciones
//
//int guardarDataEnSHM(int pidProc,struct imagenProceso *imagProc); //Guardo en SHM accion realizada sobre proceso y su imagen

int reanudarProceso(pid_t pid);

int suspenderProceso(pid_t pid);

//int accionATomar(Proceso proc, Proceso *direc);

int ejecutar(pid_t pid);

void signal_handler(int signal);

int lugarVacio(void *shm);

