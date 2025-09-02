#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int fd1, fd2;
	char buf[1];
	
	if(argc<3){
		fprintf(stderr, "usage:%s file1 file2\n", argv[0]);
		exit(-2);
	}	
	if((fd1=open(argv[1], O_RDONLY))<0){
		printf("usage:a.out file1 file2\n");
		exit(-1);}
	if((fd2=open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0666)));

	lseek(fd1, -1, SEEK_END);
	while(1){
	read(fd1, buf, 1);
	write(fd2, buf,1);
	if(lseek(fd1, -2, SEEK_CUR)==0){
		read(fd1, buf,1);
		write(fd2, buf, 1);
		break;
		}
	}
}
