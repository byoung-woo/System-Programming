#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){

	int fd[2], status=0, pid, n;
	char buf[512];
	pipe(fd);

	pid = fork();

	if(pid==0){
		close(1);
		dup(fd[1]);
		close(fd[1]);
		close(fd[0]);
		
		if(argc >1){
			execl("/bin/cat", "cat", argv[1], (char*)NULL);
		}
		else{
			execl("/bin/cat", "cat", NULL);
		}

		perror("execl");
		exit(127);
		
	}{


	close(0);
	dup(fd[0]);
	close(fd[1]);
	close(fd[0]);
	
	execl("/bin/cat", "cat", NULL);
        perror("execl");
}	
	wait(&status);
	
	return 0;
}

