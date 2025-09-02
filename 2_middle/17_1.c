#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
	int fd, n, m;
	char buf[1];
	if(argc<4){
		printf("usage:a.out file1 n m c\n");
		exit(-1);
	}

	fd=open(argv[1], O_RDWR);
	n=atoi(argv[2]);
	m=atoi(argv[3]);
	
	lseek(fd, n, SEEK_SET);
	for(int i=0; i<m; i++){
		write(fd, argv[4], 1); 
}
}
