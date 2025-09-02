#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	int fd1;
	char buf[512];
	int count;

	fd1=open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0644);

	dup2(fd1, 1);
	
	while((count=read(0, buf, 512))>0){
		buf[count]=0;
		if(buf[0]=='.')
			break;
		printf("%s", buf);
	}
 	close(fd1);
}
