#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int mysumascii(char *string){
	int sum=0;
	int len=strlen(string);
	for(int i=0; i<len; i++){
		sum+=string[i];
	}	
	return sum;
}


int main(void){
	printf("[%d]\n", mysumascii("A"));
	printf("[%d]\n", mysumascii("ABC"));
	printf("[%d]\n", mysumascii("ABCDE"));
}
