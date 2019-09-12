/**
 AUTORES: Daniel Sánchez flores
 		  Diego Charles Suárez
		 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SHUTDOWN 2U
#define EXIT     3U

int main(void)
{
	char cmd[80];
	pid_t p;
	int status;
	
	while(1)
	{
		printf("Shell >\n");
		scanf("%[^\n]%*c",cmd);
		if(strcmp("exit", cmd) == 0)
			exit(EXIT);
		else 
		{
			if (strcmp("shutdown", cmd) == 0)
				exit(SHUTDOWN);
			else
			{
				p =	fork();
				if(p == 0)
					execlp(cmd, "arg1", NULL);
				wait(&status);
			}
		}
	}
	return 0;
}