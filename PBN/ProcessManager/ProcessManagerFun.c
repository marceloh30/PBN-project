#include "ProcessManagerFun.h"

void suspenderProceso(pid_t pid){
    // SIGSTOP pausa un proceso
    kill(pid,SIGSTOP);
}

void reanudarProceso(pid_t pid){
    // SIGCONT reanuda la ejecucion
    kill(pid,SIGCONT);
}

void ejecutar(pid_t pid){
    /*Defino el manejo de la señal cuando el hijo muera
	SA_NOCLDWAIT => Evita que se cree un proceso zombie una vez que termina de ejecutarce
	SA_NOCLDSTOP => Evita que salte el manejador con las señales SIGSTOP y SIGCONT*/
	struct sigaction act;
    act.sa_handler = signal_handler;
    act.sa_flags = SA_NOCLDWAIT | SA_NOCLDSTOP;
    reanudarProceso(pid);
    sigaction(SIGCHLD,&act,NULL);
    sleep(20);
    suspenderProceso(pid);
}



int accionATomar(Proceso proc){
	
    int ret, pid;
	
	//Consigo argumentos desde proc.data y los mando a ejecutar.
	
    switch (proc.estado) {
		
        case PARA_EJECUTAR:
            
			//Crea el proceso y guarda el pid
			
            if ( ( pid = ejecProceso( proc.data , NULL) ) != -1 ) {
                
				proc.pid = pid;
                sleep(5);
                suspenderProceso(proc.pid);
                ret = 0;
				
            } else {
                ret = -1;
            }
			
            break;

        case ELIMINAR:
		
            kill(proc.pid,SIGKILL);
            ret =0;
			
            break;

        case ACTIVO:
		
            ejecutar(proc.pid);
            ret = 0;
			
            break;

        default:
		
            ret = 0;
			
            break;
    }
    
    return ret;
}

void signal_handler(int signal){
    printf("\nMurio\n");
}
