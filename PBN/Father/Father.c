#include "FatherFun.h"

//int main( int argc, char *argv[]){

int main(){
	//int puerto = atoi(argv[1]);

    Proceso listPro[100];

        void *shm = crearSHM(DIR_KEY_SHM);
        Proceso *lista;
        lista = (Proceso *)(shm + 50);
        int id = generarID(DIR_KEY_SHM);
    //    int creacionSist[] = crearProcSis[] (puerto);
        Proceso pro = {1232,"hefwef",5,"ddasdas"};
        Proceso pro1 = {1232,"hefwef",6,"ddasdas"};

            lista[0] = pro;
        lista[1]=pro1;

        printf("\nPrintf: %d-%d\n",pro1.estado,lista[1].estado);
        eliminarSHM(id);
        desconectarSHM((void *)shm);
        
        
        //Codigo para suspenderse



	return EXIT_SUCCESS;
}
