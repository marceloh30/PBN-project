//incluir senales!!!
#include "../GeneralFunctions.h"
#include <setjmp.h>
#include <signal.h>

//Macros:
//Firmas:
//int accionSHM(short int pidProceso, char *data); //Devuelve pid del proceso al cual realizó una accion
//
//void analizarSHM(void); //Es el encargado de llamar a accionSHM() y mirar proceso por proceso en SHM para realizar acciones
//
//int guardarDataEnSHM(int pidProc,struct imagenProceso *imagProc); //Guardo en SHM accion realizada sobre proceso y su imagen

void reanudarProceso(pid_t pid);

void suspenderProceso(pid_t pid);

int accionATomar(Proceso unProceso);

void ejecutar(pid_t pid);

void signal_handler(int signal);

