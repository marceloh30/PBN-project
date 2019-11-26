#ifndef _FATHERFUN_H_
#define _FATHERFUN_H_

#include "../GeneralFunctions.h"
#include "../SHM/SHMFun.h"
//#include <sys/socket.h>

//Macros
#define VAL_SHM 1234
#define DIR_R "../Receptor/Receptor"
#define DIR_PM "../ProcessManager/ProcessManager"
#define DIR_L "../Listener/ListenerManager"
#define DIR_A "../Actuador/Actuador"
#define DIR_KEY_SHM "../SHM/keyGeneratorSHM"

//Firmas
int crearProcSis ( int puerto );

#endif
