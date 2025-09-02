#include "namedPipe_13.h"

#define LOG_FILE "server.log"

int main() {
    int fdpub, fdpriv, i;
    struct msg msg;
    char command[LINESIZE], response[LINESIZE];
    int log_fd;

    // 서버의 Public FIFO 생성
    if (mknod(PUBLIC, S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        exit(1);
    }
    printf("Server is running...\n");

    // 로그 파일 열기
    log_fd = open(LOG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (log_fd == -1) {
        perror("open log file");
        exit(1);
    }

loop: // 반복을 위한 레이블
    if ((fdpub = open(PUBLIC, O_RDONLY)) == -1) {
        perror("open public fifo");
        exit(1);
    }

    while (read(fdpub, (char*) &msg, sizeof(msg)) > 0) {
        printf("Command received: %s\n", msg.command);

        // 로그 기록
        dprintf(log_fd, "%s : %s\n", msg.pipe, msg.command);

        // 클라이언트의 Private FIFO 열기
        if ((fdpriv = open(msg.pipe, O_WRONLY | O_NDELAY)) == -1){
            perror("open private fifo");
            continue;
        }

        // 명령 실행
        if (fork() == 0) {
            dup2(fdpriv, STDOUT_FILENO); // 결과를 Private FIFO로 보냄
            dup2(fdpriv, STDERR_FILENO); // 에러도 Private FIFO로 보냄
            close(fdpriv);
            execlp("/bin/sh", "sh", "-c", msg.command, NULL);
            perror("execlp");
            exit(1);
        }

        close(fdpriv);
        wait(NULL); // 자식 프로세스 대기
    }

    close(fdpub);
    goto loop;

    close(log_fd);
    unlink(PUBLIC);
    return 0;
}

