#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define LINESIZE 512

int main(int argc, char *argv[]){

	int fd[2], fd1,pid, n, status=0;
	char buf[LINESIZE];

	if (argc < 3) {
        fprintf(stderr, "Usage: %s <command> <output_file>\n", argv[0]);
        exit(1);
    }


	pipe(fd);
	fd1 = open(argv[argc-1],O_WRONLY|O_CREAT|O_TRUNC,0666);
	pid=fork();
	if(pid==0){
			close(1);
			dup(fd[1]);
			close(fd[0]);
			close(fd[1]);
			char *arg[argc];
			int i=0;
			// a.out /bin/date -a output -> argc = 4
			for(i=1;i<argc-1;i++){ // i=1; i<3; i++

				arg[i-1] = argv[i]; // arg[0] = argv[1](/bin/date)
									// arg[1] = argv[2](-a)
									
				
			}
			arg[argc-2]=NULL;		// arg[2] = NULL

			execv(arg[0],&arg[0]);		// /bin/date, /bin/date, -a, NULL 
			exit(127);
	}
	close(fd[1]);

	wait(&status);

	while((n=read(fd[0],buf,512))>0){
			write(fd1, buf, n);
	}

	close(fd[0]);
	close(fd1);
	return 0;

}



