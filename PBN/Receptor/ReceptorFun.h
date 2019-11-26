#ifndef _RECEPTORFUN_H_
#define _RECEPTORFUN_H_

//#include "Senales.h"

#include "../Sockets/SocketFunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> // open function
#include <unistd.h> // unistd.h es para fork y exec
#include <time.h>
#include <string.h>


//Macros:
#define ESCUCHA_TIME_OUT 10 //(en seg.)

//Variable para guardar pids de hijos:
//int hijos[MAX_CLIENTS];

//Firmas:
void escucharUsuarios(int puerto);
int delegarRecepc(char *userData, int sockId);

#endif
