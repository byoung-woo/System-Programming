#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){

	int fd[2], status=0;

	
	if(pipe(fd)==-1){
		perror("pipe():");
		exit(1);
	}

	if(fork()==0){
		
		char *path[] = {"/bin/ls","/bin/objcopy",NULL};
		close(1);
		dup(fd[1]);
		execv("/bin/ls",path);
		exit(127);
	}

	if(fork()==0){
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		execl("/bin/xargs","xargs","ls", "-l",(char*)0);
		exit(128);
	}

	close(fd[0]);
	close(fd[1]);
	while((wait(&status))!=-1);
	return 0;
}

