#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct{
	char name[20];
	int age;
} PERSON;

int main(int argc, char *argv[]){
	int fd1;
	PERSON p;
	long size;

	fd1=open(argv[1], O_WRONLY|O_CREAT|O_APPEND, 0600);


	while(1){
		memset(&p, 0x00, sizeof(PERSON));
		fprintf(stderr, "name: ");
		fflush(stderr);

		if((size=read(0, p.name, sizeof(p.name)))<0)
			break;
		p.name[size]=0;
		if(p.name[0]=='-')
			break;
	
		fprintf(stderr, "age: ");
		fflush(stderr);

		if((size=read(0, &p.age, sizeof(int)))<0)
			break;
		write(fd1, &p, sizeof(PERSON));
	}
	close(fd1);
	exit(-1);
}
