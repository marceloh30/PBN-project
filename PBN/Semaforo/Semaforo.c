#include "Semaforo.h"

int crearSemaforo(void *shm){
	sem_t *sem = (sem_t *)(shm + SEM_OFFSET);
	sem_init(sem,1,1);
	return 0;
}

int eliminarSemaforo(sem_t sem){
    // Retorna -1 si sem no es una direcion de semaforo valida
    return sem_close(sem);
}
