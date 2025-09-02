#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


int main(int argc, char *argv[]){
	int fd1, count;
	char buf[512];

	fd1=open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0644);
		
	dup2(fd1, 1);

	while((count=read(0, buf, 512))>0){
		buf[count]=0;
		printf("%s", buf);
	}
	close(fd1);
}
