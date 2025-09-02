#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(int argc, char *argv[]){

	int fd1[2], fd, status=0, n;

	char buf[512];

	if (argc < 3) {
        fprintf(stderr, "Usage: %s <command> <output_file>\n", argv[0]);
        exit(1);
    }
	pipe(fd1);
	
	fd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC,0666);

	if (fd == -1) {
        	perror("open error");
        	exit(1);
    	}

	if(fork()==0){
		close(1);
		dup(fd1[1]);
		close(fd1[0]);
		close(fd1[1]);
		char *cmd = argv[1];
		execl(cmd, cmd,(char*)0);
		exit(127);
	}

	//close(fd1[0]); do not close at this program
	close(fd1[1]); // close write-end -> detect EOF(in read-end)
	wait(&status);
	

	while((n=read(fd1[0],buf,sizeof(buf)))>0){
		write(fd, buf, n);
	}
	
	close(fd1[0]);              // 파이프 읽기 끝 닫기
    	close(fd);                  // 파일 닫기
    	return 0;
}

