#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	int fd1, fd2;
	char buf[256];
	long size;
	fd1=open(argv[1], O_RDONLY);
	fd2=open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644);

	dup2(fd1, 0);
	dup2(fd2, 1);
	while((size=read(0,buf, sizeof(buf)))>0)
	
		write(1, buf, size);
}
