#include "name.h"

int main(int argc, char *argv[]){
	int n, fdpub, fd;
	char line[LINE];

	if((fdpub= open(PUB, O_WRONLY))==-1){
		perror(PUB); exit(2);
	}

	fd=open(argv[1], O_RDONLY);
	while((n=read(fd, line, LINE))>0)
		write(fdpub, line, n);
	close(fd);
	exit(0);
}
