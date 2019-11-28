#include <semaphore.h>

//Macros
#define SEM_OFFSET 10

sem_t *crearSemaforo(void *shm);

int eliminarSemaforo(sem_t *sem);
