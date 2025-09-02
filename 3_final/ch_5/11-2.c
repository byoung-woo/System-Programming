#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig){

	if(sig==SIGALRM){
		printf("Timeout\n");
		exit(0);
	}

}



int main(int argc, char *argv[]){

	if(argc < 2){
		fprintf(stderr, "usage : %s [time]\n", argv[0]);
		exit(1);
	}

	int time = atoi(argv[1]);

	alarm(time);

	signal(SIGALRM, handler);
	signal(SIGINT, SIG_IGN);
	
	pause();

}
