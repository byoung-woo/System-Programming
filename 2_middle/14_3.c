#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	char buf[1];
	int fd1;

	fd1=open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0644);
	
	dup2(fd1, 1);
	printf("Hello, World\n");
	printf("Test input\n");
}
