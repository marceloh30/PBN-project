#include "Semaforo.h"

sem_t *crearSemaforo(void *shm){
	sem_t *sem = (sem_t *)(shm + SEM_OFFSET);
	sem_init(sem, 1, 1);
	return sem;
}

int eliminarSemaforo(sem_t *sem){
    // Retorna -1 si sem no es una direcion de semaforo valida
    return sem_close(sem);
}
