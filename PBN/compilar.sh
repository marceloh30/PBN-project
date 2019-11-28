#!/bin/bash

####Compila el Process Manager####
gcc -pthread -Wall GeneralFunctions.h GeneralFunctions.c Semaforo/Semaforo.h Semaforo/Semaforo.c SHM/SHMFun.h SHM/SHMFun.c Sockets/SocketFunc.h Sockets/SocketFunc.c ProcessManager/ProcessManagerFun.h ProcessManager/ProcessManagerFun.c ProcessManager/ProcessManager.c -o ProcessManager/PM;

####Compila el Actuador####
gcc -pthread -Wall Semaforo/Semaforo.h Semaforo/Semaforo.c DynamicLists.h DynamicLists.c SHM/SHMFun.h SHM/SHMFun.c Sockets/SocketFunc.h Sockets/SocketFunc.c Actuador/AFun.h Actuador/AFun.c Actuador/AFun.h Actuador/Actuador.c -o Actuador/A;

####Compila el Father####
gcc -Wall GeneralFunctions.h GeneralFunctions.c Semaforo/Semaforo.h Semaforo/Semaforo.c SHM/SHMFun.h SHM/SHMFun.c Father/FatherFun.h Father/FatherFun.c Father/Father.c -o Father/F;

####Compila el Recepcionista####
gcc -pthread -Wall GeneralFunctions.h GeneralFunctions.c Sockets/SocketFunc.h Sockets/SocketFunc.c Receptor/RecepcionistaFun.h Receptor/RecepcionistaFun.c Receptor/Recepcionista.c -o Receptor/Rp;

####Compila el Receptor####
gcc -pthread -Wall  GeneralFunctions.h GeneralFunctions.c Sockets/SocketFunc.h Sockets/SocketFunc.c Receptor/ReceptorFun.h Receptor/ReceptorFun.c Receptor/Receptor.c -o Receptor/R;

####Compila el Terminal####

####Compila el generador de la key de SHM####
gcc -Wall SHM/keyGeneratorSHM.c -o SHM/keyGeneratorSHM;

echo "\n\n\n\n------------------SISTEMA COMPILADO------------------\n\n\n\n" #Genera espacio entre cada corrida
