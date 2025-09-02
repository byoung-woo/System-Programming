#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	int fd1;
	char buf[1];
	
	fd1=open(argv[1], O_RDONLY);
	dup2(fd1, 0);
//	dup2(fd1, 1);

	while(scanf("%c", buf)>0){
		printf("%c", buf[0]);
	}	

}
