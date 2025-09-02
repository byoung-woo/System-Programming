#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "namedPipe.h"

int main(int argc, char *argv[]) {
    int fdpub, fdpriv, pipe_fd[2];
    struct message msg;
    char line[LINESIZE];

    // 서버의 Public FIFO 생성
    if (mknod(PUBLIC, S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        exit(1);
    }

    printf("Server is running...\n");

    // Public FIFO 열기
    if ((fdpub = open(PUBLIC, O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }

loop:
    while (read(fdpub, &msg, sizeof(msg)) > 0) {
        printf("Command received: %s\n", msg.filename);

        // 클라이언트의 Private FIFO 열기
        if ((fdpriv = open(msg.privfifo, O_WRONLY)) == -1) {
            perror(msg.privfifo);
            continue;
        }

        // 파이프 생성
        if (pipe(pipe_fd) == -1) {
            perror("pipe");
            close(fdpriv);
            continue;
        }

        // 첫 번째 자식 프로세스: 명령 실행
        if (fork() == 0) {
            close(1);              // 표준 출력 닫기
            dup(pipe_fd[1]);       // 파이프의 쓰기 끝을 표준 출력으로 복사
            close(pipe_fd[0]);     // 읽기 끝 닫기
            close(pipe_fd[1]);     // 쓰기 끝 닫기
            execlp("/bin/sh", "sh", "-c", msg.filename, NULL); // 명령 실행
            perror("execlp");
            exit(1);
        }

        // 부모: 쓰기 끝 닫기
       close(pipe_fd[1]);

        // 두 번째 자식 프로세스: 정렬 수행 및 클라이언트 FIFO로 전달
        if (fork() == 0) {
            close(0);              // 표준 입력 닫기
            dup(pipe_fd[0]);       // 파이프의 읽기 끝을 표준 입력으로 복사
            close(pipe_fd[0]);     // 읽기 끝 닫기
            close(1);              // 표준 출력 닫기
            dup(fdpriv);           // 클라이언트 FIFO를 표준 출력으로 복사
            close(fdpriv);         // 클라이언트 FIFO 닫기
            execlp("sort", "sort", NULL); // 정렬 실행
            perror("execlp");
            exit(1);
        }

        // 부모: 읽기 끝 닫기
        close(pipe_fd[0]);
  	close(fdpriv); // 클라이언트 FIFO 닫기

        // 자식 프로세스 대기
        while (wait(NULL) > 0);
    }

    goto loop; // 무한 루프 유지
    unlink(PUBLIC); // 서버 종료 시 Public FIFO 삭제
    return 0;
}

