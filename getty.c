/**
 AUTORES: Daniel Sánchez flores
 		  Diego Charles Suárez
		 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#define HIJ0 0u
#define SHUTDOWN 2U
#define EXIT     3U
#define CMDSHIFT 8U // command shift

#define MAX_LINE_LEN 100// Maximum file line length


int  log_in(); 
int user_auth(const char * user_data);
int main()
{
	/* wait succesful log in*/
	do{ 
		 
	   }while( 0 != log_in());
	 printf("log in succesfullly  \n");
	
	
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

int  log_in(void)
{
	char user_name [80]= {'\0'};
	printf("Ingrese usuario\n");
	// pedir contraseña
	scanf("%[^\n]%*c", user_name);
	
	char user_psswd [80]= {'\0'};
	printf("Ingrese contraseña\n");
	scanf("%[^\n]%*c", user_psswd);
	strcat(user_name, (const char * )":");
	strcat(user_name, (const char * )user_psswd);
	
	return  user_auth((const char *)user_name);
}
int user_auth(const char * user_data)
{
	  FILE *fp;
   char str[60];

   /* opening file for reading */
   fp = fopen("psswd.txt" , "r");
   if(fp == NULL) {
      perror("Error opening file of psswd");
      return(-1);
   }
    int  len_user_d = strlen(user_data);

	int cntr_conciden = 0;
   while ( fgets (str, 60, fp)!=NULL ) {
     
	
	  cntr_conciden= 0;
	   int cntr = 0;
	
	   // compare str of file against user_data str
	   while(cntr< MAX_LINE_LEN )
	   {
		   
		   if( str[cntr]  == user_data[cntr] )
			   cntr_conciden++;
		   else
			   break;
		 
		   cntr++;
	   }   
	  
	   if(cntr_conciden== len_user_d)
	   {
		   return 0;
	   }
	
   }
	
   fclose(fp);
   printf("no se reconoció %s\n", user_data);
   return(-1);
  }
