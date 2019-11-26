#include "SHMFun.h"

//ftok(const char *pathname,int progid); Sirve para generar el nombre que van a usar los programas para referirce a la SHM
//lo creo en /tmp
//Hay que tener creado el archivo cuando se crea memoria compartida, se crea con el sistema
//shmget(); size => el sistema operativo te redondea a un valor 
// flags => IPC_CREAT | IPC_EXCL 
/* shmat() el segundo parametro se pone en NULL, no nos interesa
shmdt() => desengancha un procesos de la SHM. Lo correcto es desenganchar el proceso antes de que se cierre
shmctl() sirve para marcar la memoria compartida para que sea borrada
Si se pasa IPC_RMID, se ignora el tecer parametro
La memoria se elimina solamente cuando no hay ningun proceso conectado
ipcrm
ipcmk
*/
//EEXIST fILE EXIST

//Codigo
void *crearSHM(char *path){
    // Si retorna -1, hubo un error en shmat()
    // Si retorna NULL, hubo un error al generar la id
    int id;
    void *shmp = NULL;
    
    if( (key = ftok(path,SHM_ID)) == -1 ){
        perror("Error al generar key: ");
    }else {
    	if( (id = shmget(key, SHM_SIZE, IPC_CREAT | IPC_EXCL)) == -1 ){
            perror("Error al generar la ID: ");
            if( errno == EEXIST ) eliminarSHM(path);
    	} else {
            shmp = shmat(id, NULL, 0);
            perror("Error al crear SHM: ");
            printf("%d\n",id);
        }
    }
        
    return shmp;
}

void *conectarSHM(char *path){
    // Si retorna -1, hubo un error en shmat()
    // Si retorna NULL, hubo un error al generar la id
    int id;
    void *shmp = NULL;
    
    if( (generarID(path) = id) != -1 ){
        shmp = shmat(id, NULL, 0);
        perror("Error al conectarce a la SHM: ");
        printf("%d\n",id);
    }
        
    return shmp;
}

int eliminarSHM(char *path){
    int id, ret;
    
    if( (generarID(path) = id) == -1 ){
        ret = shmctl(id, IPC_RMID, NULL);
        perror("\nError al eliminar SHM: ");
    }
    
    return ret;
}
     
int desconectarSHM(char *path){
    int ret = -1;
    void *shmp;
    
    if( generarID(path) != -1 ){
        if( (shmp = shmat(id, NULL, 0)) == -1 ){
            perror("\nError al desconectarce de SHM: ");
        } else{
            ret = shmdt(shmp);
            perror("\nError al desconectarce de SHM: ");
        }
    }
    
    return ret;
}

int generarID(char *path){
    int id = -1;
    key_t key;
    
    if( (key = ftok(path,SHM_ID)) == -1 ){
        perror("\nError al generar key: ");
    } else{
        id = shmget(key, SHM_SIZE, 0);
        perror("\nError al generar la ID: ");
    }
              
    return id;
}
