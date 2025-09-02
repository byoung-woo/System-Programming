#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	int sum=0;
	int num;

	for(int i=1; i<argc; i++){
		num=atoi(argv[i]);
//		printf("%d\n", num);		
		sum=sum+num;
	}
	printf("%d\n", sum);
}
