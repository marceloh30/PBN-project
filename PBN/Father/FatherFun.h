#include "../GeneralFunctions.h"
#include "../SHM/SHMFun.h"

//Macros
#define DIR_R "../Receptor/Receptor"
#define DIR_PM "../ProcessManager/ProcessManager"
#define DIR_L "../Listener/ListenerManager"
#define DIR_A "../Actuador/Actuador"
#define DIR_KEY_SHM "../SHM/keyGeneratorSHM"

//Firmas
int *crearProcSi ( int puerto );

void eliminarSistema(int *arg);
