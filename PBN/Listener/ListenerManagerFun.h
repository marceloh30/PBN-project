//#include "SocketServer.h"
//#include "Senales.h"
//#include "Pipes.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "../FatherFun.h"

//Macros:
#define DIRECION_CL "Listener/Listener"
#define DIRECION_L "./Listener"
#define TIME_OUT_CONECTION 10000

//Firmas:
int delegarListener(char *prossessData);
