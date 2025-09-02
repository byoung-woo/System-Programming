#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int mystrlen(char *string){
	int len=0;
	while(string[len] != '\0')
		len++;
	return len;
}

int main(){
		printf("%d\n", mystrlen("This"));
		printf("%d\n", mystrlen("This is"));
		printf("%d\n", mystrlen("This is test"));
}
