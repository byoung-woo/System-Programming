#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
int main(int argc, char *argv[]){


	int fd[2], status=0, n;
	int file_fd;
	char buf[512];

	pipe(fd);
	file_fd=open(argv[1], O_RDONLY);
	
	if(fork()==0){
		close(fd[1]);
		while((n=read(fd[0], buf, sizeof(buf)))>0){
			write(1, buf, n);
		}
		close(fd[0]);
		
		exit(127);
	}

	else {	
		close(fd[0]);

		file_fd=open(argv[1], O_RDONLY);

		while((n= read(file_fd, buf, sizeof(buf)))>0){
			write(fd[1], buf, n);
		}

		close(file_fd);
		close(fd[1]);
		wait(&status);
	}
	return 0;



}

