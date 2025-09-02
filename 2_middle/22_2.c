#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[]){
	int fd1, fd2, size;
	char buf1[1], buf2[256];

	if(argc<3){
		printf("usage:a.our file1 file\n");
		exit(-1);
	}
	fd1=open(argv[1], O_WRONLY);
	fd2=open(argv[2], O_RDONLY);

	lseek(fd1, -1, SEEK_END);
	while((size=read(fd2, buf2, 256))>0){
		write(fd1, buf2, size);
	}
	

	
	
	
	
}
