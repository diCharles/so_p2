/**
 AUTORES: Daniel Sánchez flores
 		  Diego Charles Suárez
		 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define HIJ0 0u
#define SHUTDOWN 2U
#define EXIT     3U
#define CMDSHIFT 8U // command shift


int  log_in(); 

int main()
{
	/* wait succesful log in*/
	while(1 != log_in());
	
	
	/* crear hijo*/
	pid_t p;
	int status_hijo ;
	FILE * dummy;
	
	p=fork();
	if(p == HIJ0)  
	{
		/* child will become shell*/
		execlp("./sh", "sh", NULL);
	}
	// ahora revisa y espera el status de terminacion de shell
		
		wait(& status_hijo);
		status_hijo = status_hijo>>CMDSHIFT;
	
		if(EXIT == status_hijo )
		{
			//Sale y ya, por lo que init abrira otro proceso getty
			exit(EXIT);
		}
		else if(SHUTDOWN == status_hijo )
		{
			//Crea el archivo bandera que hace que hace que init cierre todo
			dummy = fopen("flag.txt", "w");
			fclose(dummy);
			//Despues cierra el proceso
			exit(SHUTDOWN);
		}	
	
		//printf("getty final with  process %d shutdown\n",getpid());
	
	return 0;
}	

int  log_in()
{
	char dummy [80];
	printf("Ingrese usuario y contrasena\n");
	// pedir contraseña
	scanf("%[^\n]%*c", dummy);
	// seguir hasta contraseña correcta
	return (1);
}