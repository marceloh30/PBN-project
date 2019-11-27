#ifndef _FUNMENUS_H_
#define _FUNMENUS_H_

#include "ConsolaFun.h"

//Macros:
#define STR_MI "\nMenú Inicial:\n 1- Conectar al Sistema \n 2- Salir \n"
#define STR_MP "\nMenú Principal:\n1- Crear / Borrar Proceso\n2- Suspender / Reanudar Proceso\n3- Ver Estado de un Proceso\n4- Mostrar Lista de Procesos Creados (por Sesion o Planificador)\n5- Ver salida de un proceso\n6- Cerrar sesión (Vuelvo al menu inicial)\n7- Cerrar Sistema (Vuelvo al menu inicial)\n"
#define STR_SM1 "\nSub menu 1:\n1- Crear Proceso \n2- Borrar Proceso \n3- Volver al Menu Principal \n"
#define STR_SM2 "\nSub menu 2:\n1- Suspender Proceso \n2- Reanudar Proceso \n3- Volver al Menu Principal \n"

//Firmas:
void menuPrincipal(int socket);
void menuInicial(void);
void Submenu1(int socket);
void Submenu2(int socket);

#endif
