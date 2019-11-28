#!/bin/bash

gcc -pthread -Wall GeneralFunctions.h GeneralFunctions.c Semaforo/Semaforo.h Semaforo/Semaforo.c SHM/SHMFun.h SHM/SHMFun.c ProcessManager/ProcessManagerFun.h ProcessManager/ProcessManagerFun.c ProcessManager/ProcessManager.c;

gcc -pthread -Wall Semaforo/Semaforo.c DynamicLists.c SHM/SHMFun.c Sockets/SocketFunc.c Actuador/AFun.c Actuador/Actuador.c;

gcc 
