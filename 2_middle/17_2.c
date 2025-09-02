#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
	int fd1, fd3, num;
	char buf, buf3;
	if(argc<3){
		printf("usage:a.ut file1 num file2\n");
		exit(-1);
	}

	fd1=open(argv[1], O_RDONLY);
	fd3=open(argv[3], O_WRONLY|O_CREAT|O_TRUNC, 0644);
	
	num=atoi(argv[2]);

	while(read(fd1, &buf, 1)>0){
		buf3=buf+num;
		write(fd3, &buf3, 1);	
	}
}
