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
}person;

int main(int argc, char *argv[]){
	int fd1; 
	long size;
	person ps;
	
	fd1=open(argv[1], O_WRONLY|O_CREAT|O_EXCL, 0640);

	while(1){
		memset(&ps, 0x00, sizeof(person));
		fprintf(stderr, "name: "); // stderr는 입력전 버퍼링 없이 바로 출력되기 때문에 사용, stdout은 버퍼링 걸림
		fflush(stderr); // 출력스트림 버퍼를 비워줘서 바로 출력;
		if((size=read(0, ps.name, sizeof(ps.name)))<0)
			break;
		ps.name[size]=0; // 마지막 부분에 널값을 채움
		if(ps.name[0]=='*') // 첫부분에 *가 들어가면 break
			break;
		
		fprintf(stderr, "age: "); 
		fflush(stderr);
		if((size=read(0, &ps.age, sizeof(int)))<0)
			break;
		write(fd1, &ps, sizeof(person));
	}
	
	close(fd1);
	exit(0);
}
