#include "AFun.h"

char *leerDatos (char *buf, void *shm) {

	//Obtengo Semaforo para shm:
	sem_t *sem = (sem_t *) (shm + SEM_OFFSET);
	//Dejo puntero en el offset donde comienzan los procesos:
	shm += PROC_OFFSET;

	char bufTmp[BUF_SIZE];
	strcpy(bufTmp, buf);
	
	char ret[BUF_SIZE];
	char *saveptr;
	
	//Interpreto mensaje:
	int accion = atoi ( strtok_r (bufTmp, ",", &saveptr) );
	int datoNum = atoi ( strtok_r (NULL, ",", &saveptr) ); //datoNum: Un filtro para lista o un pid determinado.
	char *data = strtok_r (NULL, ",", &saveptr);
	int socket = atoi ( strtok_r (NULL, ",", &saveptr) ); //Para devolverle el dato a ese socket.
	
	int paraWrite = 0; //Lo dejo en 0 para que sea false (al no ser que lo cambie el código)
	
	switch (accion) {
		
		case ACT_LISTA: {
			paraWrite = WRITE_SOCK;
			sprintf(ret, "%d,%d,%s", paraWrite, ACT_LISTA, generarLista(datoNum, socket, (Proceso *)shm, sem));
			break;
		}
		
		case ACT_EST: {
			
			paraWrite = WRITE_SOCK;
			sprintf(ret, "%d,%d,%d", paraWrite, ACT_EST, getEstado(datoNum, (Proceso *)shm, sem));
			break;
		}
		
		case ACT_REAN: {
			
			setEstado(datoNum, ACTIVO, (Proceso *)shm, sem);	
			paraWrite = WRITE_SOCK;
			sprintf(ret, "%d,%d,%d", paraWrite, ACT_REAN, datoNum);
			break;
		}
		
		case ACT_SUSP: {

			//Envio SIGSTOP para suspenderlo
			kill(datoNum, SIGSTOP);
			setEstado(datoNum, SUSPENDIDO, (Proceso *)shm, sem);

			paraWrite = WRITE_SOCK;
			sprintf(ret, "%d,%d,%d", paraWrite, SUSPENDIDO, datoNum);
			break;
		}
		
		case ACT_CREAR: { 			
			Proceso *ubicSHM;
			if ( (ubicSHM = getUbicacionLibre((Proceso *)shm, sem)) != NULL ) {
				crearProcSHM (datoNum, NUEVO, data, socket, ubicSHM, sem);
			}
			else {
				paraWrite = ERROR_PRC;
			}
			
			sprintf(ret, "%d,%d", paraWrite, ACT_CREAR);			
			break;
		}
		
		case ACT_BORRAR: {
			
			//Envio SIGKILL para terminar el proceso
			kill(datoNum, SIGKILL);
			//Luego lo pongo como eliminado para "liberar" 
			//el espacio asignado para ese proc.
			setEstado(datoNum, ELIMINADO, (Proceso *)shm, sem);

			paraWrite = WRITE_SOCK;
			sprintf(ret, "%d,%d,%d", paraWrite, ELIMINADO, datoNum);					
			break;
		}
		
		case ACT_ENGAN: {
			
			//paraWrite = WRITE_SOCK;
			sprintf(ret, "%d,%d", paraWrite, ACT_ENGAN);	
			break;
		}
		
		case ACT_CERR_SIST: {
			sprintf(ret, "%d,%d", paraWrite, ACT_CERR_SIST);
			kill(getppid(),SIGTERM); //Envio SIGTERM al father
			break;
		}		
			
		default: {
			
			sprintf(ret, "%d", ERROR_ACT);	
			break;
			
		}
	}
	//Devuelvo puntero a datos locales para evitar warnings.
	char *pret = ret;
	return pret;
}


//getUbicacionLibre(): Busco si hay ubicacion libre en shm y si hay devuelvo.
Proceso *getUbicacionLibre (Proceso *shm, sem_t *sem) {
	
	int i, lugarLibre = 0;
	Proceso proc;
	
	for (i = 0; (i == CANT_PROC || lugarLibre) ; i++) {
		
		proc = tomarProcSHM(shm, sem);
		
		if ( (proc.data == NULL) || (proc.estado == ELIMINADO) ) {
			lugarLibre = 1;
		}
		else {
			shm++;
			i++;
		}
	}
	
	if ( lugarLibre == 0 ) {
		shm = NULL;
	}
	
	return shm;
}

void crearProcSHM (int pid, int estado, char *data, int socket, Proceso *ubicacionLibre, sem_t *sem){

	//Genero mensaje para enviar a crearEstructura():
	char* datos = NULL;
	sprintf(datos, "%d,%d,%s,%d", pid, estado, data, socket);
	
	//Creo estuctura y la guardo en ubicacionLibre
	Proceso proc = crearEstructura(datos);

	//guardo proceso en ubicacion indicada de SHM
	guardarProcSHM(proc, ubicacionLibre, sem);

}

//devolverMsj(): Devuelve 1 si fue seteado WRITE_SOCK en el espacio 0.
int devolverMsj (char *buf) { 
	
	return atoi(buf);
}

char *generarLista (int filtro, int socket, Proceso *shm, sem_t *sem) {

	//Inicializo variables
	Proceso proc;
	char ret[BUF_SIZE];
	int i;
	int error = 0;

	//For para recorrer la SHM y observar segun filtro si debo ingresarlo en la lista a devolver
	for (i = 0; (i == CANT_PROC || !error) ; i++) {

		proc = tomarProcSHM(shm, sem);

		switch (filtro) {

			case FILTRO_SUSP: {
							
				if (proc.estado == SUSPENDIDO) { 
					(ret == NULL) ? sprintf(ret, "%d,", proc.pid) : sprintf(ret, "%s%d,", ret, proc.pid);
				}
				break;
			}
			case FILTRO_ALL | FILTRO_EST: {

				(ret == NULL) ? sprintf(ret, "%d,", proc.pid) : sprintf(ret, "%s%d,", ret, proc.pid);
				break;
			}
			case FILTRO_SP: {
				
				if (proc.sockCreador == socket) {
					(ret == NULL) ? sprintf(ret, "s-%d,", proc.pid) : sprintf(ret, "%ss-%d,", ret, proc.pid);
				}
				else { 
					(ret == NULL) ? sprintf(ret, "p-%d,", proc.pid) : sprintf(ret, "%sp-%d,", ret, proc.pid);
				}
				break;			
			}
			case FILTRO_ACT: {
				if (proc.estado == ACTIVO || proc.estado == EN_EJECUCION) {
					(ret == NULL) ? sprintf(ret, "%d,", proc.pid) : sprintf(ret, "%s%d,", ret, proc.pid);
				}
				break;				
			}
			default: {
				error = 1;
				sprintf(ret, "Filtro Erroneo.");
				break;
			}
		}
		
		shm++;
		//i++;
	}
	//Devuelvo puntero a datos locales para evitar warnings.
	char *pret = ret;
	return pret;	
}

int setEstado (int pid, int estado, Proceso *shm, sem_t *sem) {
	
	//Inicializo variables
	
	Proceso proc;	
	int ret = 0; //Inicializo en "false" y si puedo setear estado devuelvo 1
	int i;
	
	//For para recorrer shm y encontrar el pid del proceso para asignarle estado:
	
	for (i = 0; (i == CANT_PROC || (proc.estado == estado) ); i++) {
		
		proc = tomarProcSHM(shm, sem);	
		
		if (proc.pid == pid) {	
		
			proc.estado = estado;
			ret = 1;
		}
		else {
			
			shm++;
			i++;
		}
	}
	
	return ret;	
}

int getEstado (int pid, Proceso *shm, sem_t *sem) {
	
	Proceso proc;
	
	int estado = ERROR_EST;

	int i;

	for (i = 0; (i == CANT_PROC || (estado != ERROR_EST) ); i++) {
		
		proc = tomarProcSHM(shm, sem);
		
		(proc.pid == pid) ? (estado = proc.estado) : (estado = ERROR_EST);	

		shm++;
		//i++;
	}
	
	return estado;
}
