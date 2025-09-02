#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

	int fd[2], status=0;

	if(pipe(fd)==-1){
		perror("pipe");
		exit(1);
	}

	if(fork()==0){
		close(1);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		execl("/bin/ps", "ps", "-e",(char*)0);
		exit(127);
	}
	
	if(fork()==0){
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		execl("/bin/grep", "grep", "child",(char*)0);
		exit(128);
	}
	close(fd[0]);
	close(fd[1]);
	wait(&status);
	wait(&status);

	return 0;



}

