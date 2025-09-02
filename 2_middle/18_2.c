#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]){
	char ch;
	int fd1, fd2;

	fd1=open(argv[1], O_RDONLY);
	fd2=open(argv[2], O_WRONLY|O_CREAT|O_EXCL, 0644);
	
	dup2(fd1, 0);
	dup2(fd2, 1);

	while(scanf("%c", &ch)>0){
		printf("%c", ch);
	}
}
