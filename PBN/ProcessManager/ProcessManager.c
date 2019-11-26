#include "ProcessManagerFun.h"

int main(){
    printf("Manejador de procesos creado\n");
    pid_t pid;
    if((pid = fork()) == 0){
        execl("./Proceso","./Proceso",NULL);
    }
    sleep(6);
    suspenderProceso(pid);
    sleep(6);
    ejecutar(pid);
    
    return 0;
}

