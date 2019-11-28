#include "ProcessManagerFun.h"

volatile int salir;
void signal_handler( int signal );

int main( int arg, char *datos[]) {
    Proceso *shm;
    Proceso unProc;
    int aux;
    char *enviar;
    int ret;
    
    //-----//Captura la señal para eliminarce
    //SA_NOCLDWAIT => Evita que queden procesos zombies cuando llega la señal de un hijo que murio
    //SA_NOCLDSTOP => La SIGCHLD se genera cuando muere el hijo
    struct sigaction act;
    act.sa_handler = signal_handler;
    act.sa_flags = SA_NOCLDWAIT | SA_NOCLDSTOP;
    sigfillset(&act.sa_mask); //Ignora todas las señales duerante el handler
    sigaction(SIGALRM, &act, NULL);
    sigaction(SIGCHLD, &act, NULL);
    sigaction(SIGTERM, &act, NULL);
    //-----//
    
    if( (shm = conectarSHM(DIR_KEY_SHM)) != (void *)(-1) ){
        sem_t *sem = (sem_t *)(shm + SEM_OFFSET);
        int i = 0;
        
        while( salir == 0 ){
            aux = accionATomar(shm + PROC_OFFSET + i, sem);
            
            if( aux == NO_CREADO ){
                enviar = crearArray( tomarProcSHM(shm + PROC_OFFSET + i, sem) );
                //IMFORMAR AL USUARIO QUE NO SE CREO
            }
                                          
            if( aux == CREADO ){
                enviar = crearArray( tomarProcSHM(shm + PROC_OFFSET + i, sem) );
                //INFORMAR AL USUARIO QUE SE CREO
            }
            
            i++;    //Incrementa el contador
            if( i == 99 ){
                i = 0;
            }    //Reinicia el contador
            
        }
        
        ret = EXIT_SUCCESS;
        eliminarProcesos(shm + PROC_OFFSET, sem);
        desconectarSHM(shm);
    } else {
        ret = EXIT_FAILURE;
    }
    
    return ret;
}
                                    

void signal_handler( int signal ){
    switch (signal) {
            
        case SIGTERM:
            salir = 1;
            break;
            
        case SIGCHLD:
            break;
            
        default:
            break;
    }
}
