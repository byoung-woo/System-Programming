#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	int fd1;
	char buf[128];
	int count=0;

	fd1=open(argv[1], O_RDONLY);

	dup2(fd1, 0);
	
	while((scanf("%s", buf))!=EOF){
		if(strcmp(buf, argv[2])==0)
			count++;
	}
	if(count>0)
		printf("Found\n");
	else
		printf("Not found\n");
}
