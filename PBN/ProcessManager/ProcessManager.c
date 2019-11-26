#include "ProcessManagerFun.h"


int main(int arg, char *datos[]){
    Proceso *shm;
    Proceso unProc;
    int i = 0;
    
    //-----// Captura la señal para eliminarce
    struct singaction act;
    act.sa_handler = signal_handler;
    sigaction(SIGTERM,&act,NULL);
    sigfillset(act.sa_mask); //Ignora todas las señales durante el handler
    //-----//
    
    printf("Manejador de procesos creado\n");
    shm = conectarSHM("../SHM/kayGeneratorSHM.c");

    while(1){
        if( accionATomar(*(shm + i), shm + i) == PM_ERROR ){
            printf("Error al crear proceos X");
            crearArray(*aux);
            //retorna los datos del proceso
        }
        i++;
        if( i == 99 ) i = 0;
    }
    
//    desconectarSHM(shm);
    return 0;
}

