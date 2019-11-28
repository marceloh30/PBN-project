#include "SHMFun.h"

//Codigo
void *crearSHM(char *path) {
    // Si retorna -1, hubo un error en shmat()
    // Si retorna NULL, hubo un error al generar la id
    int id;
    void *shmp = NULL;
    key_t key;
    
    if( (key = ftok(path,SHM_ID)) == -1 ){
        perror("Error al generar key: ");
    }else {
    	if( (id = shmget(key, SHM_SIZE, 0666 | IPC_CREAT | IPC_EXCL) ) == -1 ){
            perror("Error al generar la ID: ");
            if( errno == EEXIST ) eliminarSHM(id);
    	} else {
            if ( (shmp = shmat(id, NULL, 0)) == (void *)-1 ) perror("Error al crear SHM: ");
        }
    }
        
    return shmp;
}

void *conectarSHM(char *path) {
    // Si retorna -1, hubo un error en shmat()
    // Si retorna NULL, hubo un error al generar la id
    int id;
    void *shmp = NULL;
    
    if( (id = generarID(path)) != -1 ) {
        if( (shmp = shmat(id, NULL, 0)) == (void *)-1) perror("Error al conectarce a la SHM: ");
    }
        
    return shmp;
}

int eliminarSHM(int id) {
    int ret;
    
    if( (ret = shmctl(id, IPC_RMID, NULL)) == -1) perror("\nError al eliminar SHM: ");
    
    return ret;
}
     
int desconectarSHM(void *shmp) {
    int ret = -1;
    
    if( (ret = shmdt(shmp)) == -1 ) perror("\nError al desconectarce de SHM: ");
    
    return ret;
}

int generarID(char *path) {
    int id = -1;
    key_t key;
    
    if( (key = ftok(path,SHM_ID)) == -1 ) {
        perror("\nError al generar key: ");
    } else{
        if ( (id = shmget(key, SHM_SIZE, 0)) == -1) perror("\nError al generar la ID: ");
    }
              
    return id;
}

Proceso crearEstructura(char *proArray) {
    Proceso unProceso;
    
    unProceso.pid = atoi(strtok(proArray,","));
    unProceso.data = strtok(NULL,",");
    unProceso.estado = atoi(strtok(NULL,","));
    unProceso.sockCreador = atoi(strtok(NULL,","));
    
    return unProceso;
}

char *crearArray(Proceso unProceso) {
    char *retorno = NULL;
    
    sprintf(retorno,"%d,%s,%d,%d",unProceso.pid,unProceso.data,unProceso.estado,unProceso.sockCreador);

    return retorno;
}

Proceso tomarProcSHM(Proceso *lista, sem_t *sem){
    Proceso proceso;
    sem_wait(sem);
    proceso = *lista;
    sem_post(sem);
    return proceso;
}

void guardarProcSHM(Proceso proc, Proceso *lista, sem_t *sem){
    sem_wait(sem);
    *lista = proc;
    sem_post(sem);
}
