#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SHUTDOWN 2U
#define SHUTSHIFT 8

void nuevo_proceso(void);

int main (void)
{
	FILE * flag;
	pid_t p;
	int status = 0;
	//Creacion de los 6 hijos
	for(int cont = 0; cont < 6; cont++)
	{
		p = fork();
		if(p == 0) //Si el proceso es un hijo, que se transforme en el proceso getty
		{
			execlp("xterm","xterm", "-e", "./getty", (char*)NULL); //Transformacion de los 6 hijos en procesos getty
		}
	}
	
	while(1)
	{
		wait(&status);
		
		flag = fopen("flag.txt", "r");
		if(flag != NULL) //Shutdown
		{
			remove("flag.txt");	
			//Elimina el resto de los hijos
			kill(0, SIGKILL);
			return 0;
		}
		else //Exit
		{
			//return 0;//QUITAR, DEBUGGING ONLY
			nuevo_proceso();
		}
		
		/*
		if(status == SHUTDOWN)
		{
			//Checa si existe el archivo bandera
			flag = fopen("flag.txt", "r");
			
			//No dejar procesos zombies
			return 0;
		}
		else
		{
			return 0;//QUITAR, DEBUGGING ONLY
			nuevo_proceso();
		}*/
	}
	
	//Shutdown
	return 0;
}

void nuevo_proceso(void)
{
	pid_t p;
	p = fork();
	if(p == 0) 
		execlp("xterm","xterm", "-e", "./getty", (char*)NULL);
}