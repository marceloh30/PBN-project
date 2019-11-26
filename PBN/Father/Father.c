#include "FatherFun.h"

//int main( int argc, char *argv[]){

int main(){
	//int puerto = atoi(argv[1]);

    Proceso listPro[100];
    void *shm = crearSHM(DIR_KEY_SHM);
    shm = listPro;
    int id = generarID(DIR_KEY_SHM);
//	int creacionSist[] = crearProcSis[] (puerto);
    Proceso pro = {1232,"hefwef",5,"ddasdas"};
    listPro[0] = pro;
    eliminarSHM(id);
    desconectarSHM(shm);
    
	
	//Codigo para suspenderse	


	return EXIT_SUCCESS;
}
