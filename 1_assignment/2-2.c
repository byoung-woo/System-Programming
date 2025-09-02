#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int size, fd1, fd2, fd3;
	char buf[1];
	
	if(argc<4){
		fprintf(stderr, "usage:%s file1 file2\n", argv[0]);
		exit(-2);
	}	
	if((fd1=open(argv[1], O_RDONLY))<0){
		printf("usage:a.out file1 file2\n");
		exit(-1);}
	if((fd2=open(argv[2], O_WRONLY|O_CREAT|O_EXCL, 0644)));
	if((fd3=open(argv[3], O_WRONLY|O_CREAT|O_EXCL, 0644)));

	while(read(fd1, buf, 1)>0){
	write(fd2, buf, 1);
	lseek(fd1, 1, SEEK_CUR);
	}
	lseek(fd1, 1, SEEK_SET);
	while(read(fd1, buf, 1)>0){
	write(fd3, buf, 1);
        lseek(fd1, 1, SEEK_CUR);
        }
	close(fd1); close(fd2); close(fd3);
	printf("\n");
}
