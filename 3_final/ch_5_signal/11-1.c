#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void handler(int sig){

	if(sig==SIGINT){
		printf("control C\n");
	}
	else if(sig==SIGQUIT){
		printf("control \\(SIGQUIT)\n");
		exit(0);
	}


}

int main(){

	int n;
	char buf[128];

	while(1){
		n=read(0,buf,sizeof(buf));
		write(1,buf,n);
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);

	}



}

