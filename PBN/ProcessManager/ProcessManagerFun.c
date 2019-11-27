#include "ProcessManagerFun.h"

int suspenderProceso(pid_t pid){
    // SIGSTOP pausa un proceso
    return kill(pid,SIGSTOP);
}

void reanudarProceso(pid_t pid){
    // SIGCONT reanuda la ejecucion
    kill(pid,SIGCONT);
}

int ejecutar(pid_t pid){
   // int *ret = NULL;
    //SIGALRM
    /*Defino el manejo de la señal cuando el hijo muera
	SA_NOCLDWAIT => Evita que se cree un proceso zombie una vez que termina de ejecutarce
	SA_NOCLDSTOP => Evita que salte el manejador con las señales SIGSTOP y SIGCONT*/
    
    //Timer
    struct itimerval cont;
    struct timeval time1 = {TIEMPO_SEC,TIEMPO_MILISEC};
    struct timeval time2 = {0,0};
    cont.it_interval = time2;   // Le dice al timer que no se reinicie
    cont.it_value = time1;      //Tiempo del timer
    setitimer(ITIMER_REAL,&cont,NULL);
    
struct sigaction act;
    act.sa_handler = signal_handler;
    act.sa_flags = SA_NOCLDWAIT | SA_NOCLDSTOP;
    sigaction(SIGALRM,&act,NULL);
	sigaction(SIGCHLD,&act,NULL);

    //int var;
    reanudarProceso(pid);
    pause();
    //if((var = wait(ret))!=0) printf("%d",var);
    printf("%d",suspenderProceso(pid));
	return 0;
}

//int accionATomar(Proceso proc, Proceso *direc){
//
//    int ret, pid;
//
//	//Consigo argumentos desde proc.data y los mando a ejecutar.
//
//    switch (proc.estado) {
//
//        case NUEVO:
//
//			//Crea el proceso y guarda el pid
//
//            if ( ( pid = ejecProceso( proc.data , NULL) ) != -1 ) {
//
//				proc.pid = pid;
//                sleep(5);
//                suspenderProceso(proc.pid);
//
//
//                ret = 0;
//
//            } else {
//                ret = -1;
//            }
//
//            break;
//
//        case ELIMINAR:
//
//            kill(proc.pid,SIGKILL);
//            proc.estado = ELIMINADO;
//            *direc = proc;
//            ret =0;
//
//            break;
//
//        case ACTIVO:
//
//            proc.estado = EN_EJECUCION;
//            ejecutar(proc.pid);
//            proc.estado = ACTIVO;
//            ret = 0;
//
//            break;
//
//        default:
//
//            ret = 0;
//
//            break;
//    }
//
//    return ret;
//}

void signal_handler( int signal ){
    printf("\nMurio\n");
}

//void eliminarProcesos(Proceso *lista){
//    Proceso unPro;
//
//    for( int i = 0; i < 100; i++ ){
//        unPro = *(lista + i);
//        if( unPro.estado != ELIMINADO && unPro.estado != NULL ){
//            kill(unPro.pid, SIGKILL);
//        }
//    }
//}

