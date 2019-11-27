#include <semaphore.h>
#include <sys/types.h>

//Macros
#define SEM_OFFSET 10

int crearSemaforo(void *shm);

int eliminarSemaforo(sem_t sem);
