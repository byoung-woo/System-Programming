#include "name.h"

int main(int argc, char *argv[]){
	int fdpub, fd, n;
	char line[LINE];

	mknod(PUB, S_IFIFO|0666, 0);

	if((fdpub=open(PUB, O_RDONLY))==-1){
		perror(PUB); 
		exit(1);
	}
loop:
	while((n=read(fdpub, line, LINE))>0){
		printf("client request arrived\n");
		write(1, line, n);
		}
	goto loop;
}
