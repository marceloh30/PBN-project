#include "FatherFun.h"

int main( int argc, char *argv[]){
    void *shm;
    int id;
    int *creacionSis;
    int puerto;

    //-----// Captura la señales al terminar los procesos
    struct sigaction act;
    act.sa_handler = signal_handler;
    act.sa_flags = SA_NOCLDWAIT | SA_NOCLDSTOP;
    sigaction(SIGALRM, &act, NULL);
    sigaction(SIGCHLD, &act, NULL);
    sigaction(SIGTERM, &act, NULL);
    //-----//
    
    if( (shm = crearSHM(DIR_KEY_SHM)) != (void *)-1 ){
        sem_t *sem = crearSemaforo(shm);
        puerto = atoi(argv[1]);
        creacionSis = crearProcSis(puerto);
        if( creacionSis[0] == EXIT_SUCCESS){
            id = generarID(DIR_KEY_SHM);
            pause();
            eliminarSistema(creacionSis, id, shm, sem);
        }
    } else printf("\nNo ejecuto sistema\n");
    
    return EXIT_SUCCESS;
}
