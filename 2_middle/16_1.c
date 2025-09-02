#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	int fd1, fd2;
	int count=0;
	char ch[256];
	fd1=open(argv[1], O_RDONLY);
	
	dup2(fd1, 0);

	while((scanf("%s", &ch))>0){
		if((strcmp(ch, argv[2]))==0)
			count++;
	}
	printf("%d\n", count);
}
