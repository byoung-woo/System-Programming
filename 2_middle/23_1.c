#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]){
	int fd1, fd2;
	char buf1[256], buf2[256];
	if(argc<3){
		fprintf(stderr, "usage:a.out file1 file2");
		fflush(stderr);
		exit(-1);
	}
	if((fd1=open(argv[1], O_RDONLY))<0){
		printf("usage:a.out file1\n");
		exit(-2);
	}
	if((fd2=open(argv[2], O_RDONLY))<0){
		printf("usage:a.out file2\n");
		exit(-3);
	}

	while(read(fd1, buf1, 256)>0){
		printf("%s", buf1);
	}
	while(read(fd2, buf2, 256)>0){
		printf("%s", buf2);
	}
	if((strcmp(buf1, buf2))==0){
		printf("identical\n");
	}
	else
		printf("different\n");
}

