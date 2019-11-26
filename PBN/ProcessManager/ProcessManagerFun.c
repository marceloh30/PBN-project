#include "ProcessManagerFun.h"

int suspenderProceso(pid_t pid){
    // SIGSTOP pausa un proceso
    return kill(pid,SIGSTOP);
}

int reanudarProceso(pid_t pid){
    // SIGCONT reanuda la ejecucion
    kill(pid,SIGCONT);
}

int ejecutar(pid_t pid){
   /*Defino el manejo de la señal cuando el hijo muera
   SA_NOCLDWAIT => Evita que se cree un proceso zombie una vez que termina de ejecutarce
   SA_NOCLDSTOP => Evita que salte el manejador con las señales SIGSTOP y SIGCONT
   SIGALRM => Señal de timer*/
   
   //-----// Timer
   struct itimerval cont;
   struct timeval time1 = {TIEMPO_SEC,TIEMPO_MILISEC};
   struct timeval time2 = {0,0};
   cont.it_interval = time2;   // Le dice al timer que no se reinicie
   cont.it_value = time1;      //Tiempo del timer
   setitimer(ITIMER_REAL,&cont,NULL);
   //-----//
   
   //-----// Manejo de señales
   struct sigaction act;
   act.sa_handler = signal_handler;
   act.sa_flags = SA_NOCLDWAIT || SA_NOCLDSTOP;
   sigaction(SIGALRM,&act,NULL);
   sigaction(SIGCHLD,&act,NULL);
   //-----//
   
   reanudarProceso(pid);
   pause();    //Pone en pausa el proceso hasta que se active el signal handler
   //Retorna -1 si el procesos termino
   return suspenderProceso(pid);
}

int accionATomar(Proceso *direc){

    int ret, pid;
    Proceso proc = *direc;

	//Consigo argumentos desde proc.data y los mando a ejecutar.

    switch (proc.estado) {

        case NUEVO:

			//Crea el proceso y guarda el pid

            if ( ( pid = ejecProceso( proc.data , NULL) ) != -1 ){
				proc.pid = pid;
                
                if( suspenderProceso(proc.pid) != -1 ){
                    
                    ret = ejecutar(pid);
                    
                } else ret FINALIZO;
                
            } else {
                
                ret = NO_CREADO;
                
            }

            break;

        case ELIMINAR:

            kill(proc.pid,SIGKILL);
            proc.estado = ELIMINADO;
            *direc = proc;
            ret =0;

            break;

        case ACTIVO:

            proc.estado = EN_EJECUCION;
            *direc = proc;
            ejecutar(proc.pid);
            proc.estado = ACTIVO;
            ret = 0;

            break;

        default:

            ret = 0;

            break;
    }

    return ret;
}

void signal_handler( int signal ){
    switch (signal) {
        case SIGTERM:
            
            break;
            
        default:
            break;
    }
    printf("\nMurio\n");
}

//void eliminarProcesos(Proceso *lista){
//    Proceso unPro;
//
//    for( int i = 0; i < 100; i++ ){
//        if( lugarVacio(lista + i) != 1){
//            kill(unPro.pid, SIGKILL); cambiar kill(0,SIGKILL);
//        }
//    }
//}

