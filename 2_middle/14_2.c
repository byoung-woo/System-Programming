#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	int fd1, loc;
	char str;
	fd1=open(argv[1], O_RDWR);
	loc=atoi(argv[2]);
	str=strlen(argv[3]);
	
	lseek(fd1, loc, 1);
	write(fd1, argv[3], str);
}
