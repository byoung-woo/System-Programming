#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int sec; // 제한 시간 저장

void handler(int sig);

int main(int argc, char *argv[]) {
    int pid, status = 0;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <program> <time>\n", argv[0]);
        exit(1);
    }

    sec = atoi(argv[2]); // 시간 값 변환

    pid = fork(); // 자식 프로세스 생성

    if (pid == -1) {
        perror("fork error");
        exit(1);
    }

    if (pid == 0) { // 자식 프로세스
        execl(argv[1], argv[1], (char *)0); // argv[1] 실행
        perror("execl error"); // execl 실패 시 오류 출력
        exit(127);
    }

    // 부모 프로세스
    signal(SIGALRM, handler); // SIGALRM 핸들러 설정
    alarm(sec);              // 제한 시간 설정

	if(wait(&status)!=-1){
		alarm(0);
		printf("Parent: child exit within %d seconds\n", sec);
		exit(0);
	}
    return 0;
}

void handler(int sig) {
    if (sig == SIGALRM) {
        printf("Parent: child killed after %d seconds\n", sec);
        kill(0, SIGKILL); // 자식 프로세스 강제 종료
        exit(0);
    }
}

