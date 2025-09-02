#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 64

int main(int argc, char *argv[]){

	int fd[2], status=0;

	char filename[SIZE];

	//create pipe
	if(pipe(fd)==-1){
		perror("pipe(): ");
		exit(1);
	}

	//child 1
	if(fork()==0){
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		read(0, filename, SIZE);
		execl("/bin/cat","cat",filename,(char*)0);
		exit(127);
		
	}
	
	//child 2
	if(fork()==0){
		close(1);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		printf("%s", argv[1]);
		exit(0);
	}

	close(fd[0]);
	close(fd[1]);
	    while(wait(&status)>0);

	return 0;
}

