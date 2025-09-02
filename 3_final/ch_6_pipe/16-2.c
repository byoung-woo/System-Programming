#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]){


	int fd, status=0, pid, n;
	
	int pip[2];

	char buf[128];

  	if (argc != 3) {
        fprintf(stderr, "Usage: %s <program> <output_file>\n", argv[0]);
        exit(1);
    }

	fd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC,0666);

	pipe(pip);

	pid = fork();

	if(pid==0){
		close(1);
		dup(pip[1]);
		close(pip[0]);
		close(pip[1]);
		execl(argv[1], argv[1], (char*)NULL);
		exit(129);
	}
	close(pip[1]);
	close(0);
	dup(pip[0]);
	
	wait(&status);

	while((n=read(0, buf, sizeof(buf)))>0){
		write(fd, buf, n);
	}
	close(pip[0]);
	//close(fd);
	exit(0);


}

