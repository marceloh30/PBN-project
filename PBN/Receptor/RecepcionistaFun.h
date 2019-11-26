#ifndef _RECEPCIONISTAFUN_H_
#define _RECEPCIONISTAFUN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../Sockets/SocketFunc.h"


//Firmas:

void cursoNormalRp(int socketC);
int buscarCantidad(int array[]);

char *rdFun (char *buf);
void wrFun (char *buf);

#endif
