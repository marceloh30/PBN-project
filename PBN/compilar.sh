#!/bin/bash

gcc -pthread -Wall GeneralFunctions.h GeneralFunctions.c Semaforo/Semaforo.h Semaforo/Semaforo.c SHM/SHMFun.h SHM/SHMFun.c Sockets/SocketFunc.h Sockets/SocketFunc.c ProcessManager/ProcessManagerFun.h ProcessManager/ProcessManagerFun.c ProcessManager/ProcessManager.c;

gcc -pthread -Wall Semaforo/Semaforo.h Semaforo/Semaforo.c DynamicLists.h DynamicLists.c SHM/SHMFun.h SHM/SHMFun.c Sockets/SocketFunc.h Sockets/SocketFunc.c Actuador/AFun.h Actuador/AFun.c Actuador/Actuador.h Actuador/Actuador.c;

gcc -pthread -Wall GeneralFunctions.h GeneralFunctions.c Semaforo/Semaforo.h Semaforo/Semaforo.c SHM/SHMFun.h SHM/SHMFun.c Father/FatherFun.h Father/FatherFun.c Father/Father.c

echo "\n\n\n\n\n\n\n\n" #Genera espacio entre cada corrida
