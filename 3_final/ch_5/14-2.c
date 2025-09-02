#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

int myalarm(int sec){

	struct itimerval t_val, old_val;

	if(sec==0){
		t_val.it_value.tv_sec = 0;
		t_val.it_value.tv_usec = 0;
		t_val.it_interval.tv_sec = 0;
		t_val.it_interval.tv_usec = 0;
	}
	else{
		t_val.it_value.tv_sec = sec;
		t_val.it_value.tv_usec = 0;
		t_val.it_interval.tv_sec = 0;
		t_val.it_interval.tv_usec = 0;
	}
	setitimer(ITIMER_REAL, &t_val,&old_val);
	
	return old_val.it_value.tv_sec;


}

void handler(int sig){

	if(sig==SIGALRM){
		printf("SIGALRM received\n");
	
	}

}

int main(int argc, char *argv[]){
	
	if (argc != 2) {
	        fprintf(stderr, "Usage: %s <seconds>\n", argv[0]);
        	exit(1);
    	}

	int sec = atoi(argv[1]);


	signal(SIGALRM, handler);
	
	myalarm(sec);	//if 5
	sleep(2);

	//remaining == 2
	int remaining = myalarm(3);
	printf("after sleep(2) remaining sec : %d\n", remaining);

	pause();
	
	return(0);


}

