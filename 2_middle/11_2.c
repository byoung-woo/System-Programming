#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	int fd1, fd2, len;
	char buf[256];
	long size;
	
	fd1=open(argv[1], O_RDONLY);
	fd2=open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644);
	
	memset(buf, 0x00, sizeof(buf));	

	size=read(fd1, buf, sizeof(buf));
	for(int i=0; i<size-1; i++){				
		buf[i]+=3;
	}
	write(fd2, buf, size);
 	close(fd1);
	close(fd2);
}
