#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 10

void excute_command(const char *cmd, const char *arg1, const char *arg2, const char *arg3, const char *arg4){

	execl(cmd, cmd, arg1, arg2, arg3, arg4,(char *)0);
	perror("execl");
	exit(1);
}

int main(){

	int fd1[2], fd2[2], status=0;
	int pid1, pid2, pid3;

	if(pipe(fd1)==-1){
		perror("pipe(): ");
		exit(1);
	}
	
	if(pipe(fd2)==-1){
		perror("pipe(): ");
		exit(2);
	}
	pid1=fork();
	if(pid1==0){
		close(1);
		dup(fd1[1]);
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);
		
		excute_command("/bin/ls", "-l",NULL, NULL, NULL);

	}

	pid2=fork();
	if(pid2==0){
		close(0);
		dup(fd1[0]);
		close(1);
		dup(fd2[1]);
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);
		excute_command("/bin/cut","-d"," ", "-f5-",NULL);
		

	}

	pid3=fork();
	if(pid3==0){
		close(0);
		dup(fd2[0]);
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);

		excute_command("/bin/sort",NULL,NULL,NULL,NULL);
	}

	close(fd1[0]);
	close(fd1[1]);
	close(fd2[0]);
	close(fd2[1]);

	waitpid(pid1, &status,0);
	waitpid(pid2, &status,0);
	waitpid(pid3, &status,0);

	exit(0);

}

