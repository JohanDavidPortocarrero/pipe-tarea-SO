#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

#define READ  0
#define WRITE 1
#define SIZE 512

int main(void) {
	srand(time(NULL));
	int numeroAle;
	
	pid_t pid;
  int p[2], readbytes;
  pipe( p );
  if ( (pid=fork()) == 0 ){ 
    close( p[1] );
		char text[SIZE];
    while( (readbytes=read( p[0], text, SIZE )) > 0){
			int entero = (int) strtol(text, NULL, 10);
			if( entero >= 500 ){
				printf("Mayor o igual a 500\n");
			}
			else{
				printf("Menor a 500\n");
			}
			//write( 1, text, readbytes );
		} 
    close( p[0] );
  }
  else{ 
    close( p[0] ); 

		numeroAle = rand() % 1000 + 1;
		char text[SIZE];
 		sprintf(text, "%d\n", numeroAle); 
    write( p[1], text, strlen( text ) );
		//printf("Como padre le mando a my son esto: %s", text);
 
    close( p[1] );
  }
  waitpid( pid, NULL, 0 );
  exit( 0 );
	
  return 0;
}