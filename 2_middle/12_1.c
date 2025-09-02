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
	
	while(read(fd1, buf, 1)>0){
		write(0, buf, 1);
	}
 	close(fd1);
}
