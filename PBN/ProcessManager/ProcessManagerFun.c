#include "ProcessManagerFun.h"

int suspenderProceso(pid_t pid){
    // SIGSTOP pausa un proceso
    return kill(pid,SIGSTOP);
}

int reanudarProceso(pid_t pid){
    // SIGCONT reanuda la ejecucion
    return kill(pid,SIGCONT);
}

int ejecutar(pid_t pid){
    /*Defino el manejo de la señal cuando el hijo muera
    SA_NOCLDWAIT => Evita que se cree un proceso zombie una vez que termina de ejecutarce
    SA_NOCLDSTOP => Evita que salte el manejador con las señales SIGSTOP y SIGCONT
    SIGALRM => Señal de timer*/
    int ret;
    
    //-----// Timer
    struct itimerval cont;
    struct timeval time1 = {TIEMPO_SEC, TIEMPO_MILISEC};
    struct timeval time2 = {0, 0};
    cont.it_interval = time2;   // Le dice al timer que no se reinicie
    cont.it_value = time1;      //Tiempo del timer
    setitimer(ITIMER_REAL, &cont, NULL);
    //-----//
   
    reanudarProceso(pid);
    pause();    //Pone en pausa el proceso hasta que se active el signal handler
    //Retorna -1 si el procesos termino
    return suspenderProceso(pid);
}

int accionATomar(Proceso *direc, sem_t *sem){

    int pid;
    int ret = 0;
    struct timespec time = {0, 5000};   //Defino la estructura para el contador
    Proceso proc = tomarProcSHM(direc, sem);

    switch (proc.estado) {

        case NUEVO:
            char *path = strtok(proc.data, " ");
            char *agr[] = NULL;
            int i = 0;
            
            while( arg[i] != NULL){
                arg[i] = strtok(NULL, " ");
                i++;
            }

            if ( (pid = ejecProceso( path , arg) ) != -1 ){
                
                if( suspenderProceso(pid) != -1 ){

                    proc.pid = pid;
                    proc.estado = EN_EJECUCION;
                    guardarProcSHM(proc, direc, sem);
                    
                    if( ejecutar(pid) == FINALIZO ){
                        proc.estado = ELIMINADO;
                        guardarProcSHM(proc, direc, sem);
                    } else{
                        proc.estado = ACTIVO;
                        guardarProcSHM(proc, direc, sem);
                    }
                    
                    ret = CREADO;
                    
                } else ret = NO_CREADO;
                
            } else {
                
                ret = NO_CREADO;
                
            }
            
            break;

        case ELIMINAR:
            
            kill(proc.pid, SIGTERM);
            puase();
            
            if( nanosleep(&time, NULL) != -1){
                kill(proc.pid, SIGKILL); //Si el proceso termina antes, salta el handler y nanosleep retorna -1
                pause();
            }
            
            proc.estado = ELIMINADO;
            guardarProcSHM(proc, direc, sem);
            
            break;

        case ACTIVO:

            proc.estado = EN_EJECUCION;
            guardarProcSHM(proc, direc, sem);
            
            if( ejecutar(proc.pid) == -1 ){
                proc.estado = ELIMINADO;
                guardarProcSHM(proc, direc, sem);
            } else {
                proc = tomarProcSHM(direc, sem);
                if ( proc.estado != SUSPENDIDO ){
                    proc.estado = ACTIVO;
                    guardarProcSHM(proc, direc, sem);
                }
            }

            break;

        default:
            break;
    }

    return ret;
}

void eliminarProcesos(Proceso *lista){
//    Proceso unPro;
    //kill(0,SIGKILL);
//    for( int i = 0; i < 100; i++ ){
//        if( lugarVacio(lista + i) != 1){
//            kill(unPro.pid, SIGKILL);
//        }
//    }
}
