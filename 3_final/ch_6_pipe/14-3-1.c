#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>


int main(int argc, char *argv[]){

	int fd[2], fd1, status=0, n;

	char buf[512];

	pipe(fd);

	fd1 = open(argv[1], O_RDONLY);

	if(fork()==0){
		close(fd[1]);

		while((n=read(fd[0],buf,sizeof(buf)))>0){
			write(1,buf,n);
		}
		close(fd[0]);
	}

	while((n=read(fd1,buf,sizeof(buf)))>0){
		write(fd[1],buf,n); //write pipe
	}
	close(fd[1]);
	close(fd[0]);

	wait(&status);
	exit(0);
}

