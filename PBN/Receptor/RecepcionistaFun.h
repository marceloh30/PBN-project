#ifndef _RECEPCIONISTAFUN_H_
#define _RECEPCIONISTAFUN_H_

#include "../Sockets/SocketFunc.h"

//Firmas:

void cursoNormalRp(int socketC);
int buscarCantidad(int array[]);

char *rdFun (char *buf, void *soyA);
int wrFun (char *buf);

#endif
