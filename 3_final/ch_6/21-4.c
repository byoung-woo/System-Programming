#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){

	int fd[2], status=0;

	if(pipe(fd)==-1){
		perror("pipe(): ");
		exit(1);
	}

	if(fork()==0){ //child 1
		close(1);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		execl("/bin/ls","ls","-l",(char*)0);
		exit(127);
	}
	
	if(fork()==0){ //child 2
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		execl("/bin/grep", "grep", "datafile",(char*)0);
		exit(128);
	}

	close(fd[0]);
	close(fd[1]);
	while(wait(&status)>0);
	return 0;
}

