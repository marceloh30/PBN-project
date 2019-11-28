#ifndef _RECEPTORFUN_H_
#define _RECEPTORFUN_H_

#include "../Sockets/SocketFunc.h"
#include <fcntl.h> // open function
#include <time.h>
#include <string.h>

//Macros:
#define ESCUCHA_TIME_OUT 10 //(en seg.)
#define DIRECCION_RP ./Rp

//Variable para guardar pids de hijos:
//int hijos[MAX_CLIENTS];

//Firmas:
void escucharUsuarios(int puerto);

int delegarRecepc(char *userData, int sockId);

#endif
