#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void signal_handler(int sig){
	if(sig==SIGINT){
		printf("interrupt signal\n");
	}
	else if(sig==SIGQUIT){
		exit(19);
	}

}

int main(){

	int pid, status=0;

	pid = fork();

	if(pid==0){
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		while(1){
			pause();
		}		
	}
	
	sleep(1);//중요 타이밍이 맞아야함
	
	for(int i=0;i<3;i++){
		kill(pid, SIGINT);
		sleep(2.5);
	}
	kill(pid, SIGQUIT);

	wait(&status);
	printf("parent: child's exit_code=[%x]\n",(status>>8));
	// 10진수 19가 16진수 0x1300
	return 0;


}

