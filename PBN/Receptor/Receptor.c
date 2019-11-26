
#include "ReceptorFun.h"

int main ( int argc, char *argv[] ) {

	int puerto = atoi(argv[1]);

	while ( 1 ) {

		escucharUsuarios(puerto);

	}

	return 	EXIT_SUCCESS;

}
