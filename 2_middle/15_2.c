#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	int position;
	int fd1, len;
	char *string=argv[3];

	fd1=open(argv[1], O_RDWR);

	position=atoi(argv[2]);
	len=strlen(argv[3]);
	
	lseek(fd1, position, SEEK_SET);
	write(fd1, string, len);

	lseek(fd1, -(position), SEEK_END);
	write(fd1, string, len);
	
	close(fd1);
}
