#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){

	int fd[2], status=0, p1,p2, n;
	char buf[128];

	if (argc < 2) {
        fprintf(stderr, "Usage: %s <program>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

	if(pipe(fd)==-1){
		perror("pipe(): ");
		exit(1);
	}
	
	if(fork()==0){
		close(1);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		execl(argv[1],argv[1],(char*)0);
		
	}
	if(fork()==0){
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		while((n=read(0,buf,sizeof(buf)))>0){
			write(1,buf, n);
		}
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	wait(&status);
	wait(&status);

	return 0;

}

