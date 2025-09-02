#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int count_sigint=0;
int count_sigquit=0;


void handler(int sig){

	if(sig==SIGALRM){
		printf("Time out!!\n");
		printf("SIGINT: %d\n",count_sigint);
		printf("SIGQUIT: %d\n", count_sigquit);
		exit(0);
	}
	else if(sig==SIGINT){
		count_sigint++;
	}
	else if(sig==SIGQUIT){
		count_sigquit++;
	}

}


int main(int argc, char *argv[]){

	int fd, n;
	char buf[128];
	int time = atoi(argv[2]);

	fd = open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0666);
	
	while(1){
	
	alarm(time);
	signal(SIGALRM,handler);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);

	n = read(0, buf, sizeof(buf));
	write(fd,buf,n);


	}


}

