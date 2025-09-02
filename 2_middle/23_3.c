#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	int fd1, fd2;
	char ch;
	
	if(argc<3){
		printf("usage:a.out file1 file2\n");
		exit(-1);
	}

	fd1=open(argv[1], O_RDONLY);
	fd2=open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644);

	dup2(fd1, 0);
	dup2(fd2, 1);

	while(scanf("%c", &ch)>0){
		printf("%c", ch);
	}	
}
