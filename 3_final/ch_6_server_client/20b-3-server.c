#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

struct msg {
    char pid[50];
    char command[100];
};

int main() {
    int svr_fd, cli_fd;
    struct msg message;
    char cli_pipe[64];

    // SVR 파이프 생성 (mknod 사용)
    if (mknod("SVR", S_IFIFO | 0666, 0) == -1) {
        perror("mknod SVR");
        exit(1);
    }

    printf("Server is running...\n");

    // 서버 무한 루프
    loop:
    if ((svr_fd = open("SVR", O_RDONLY)) == -1) {
        perror("open SVR");
        exit(1);
    }

    while (read(svr_fd, &message, sizeof(message)) > 0) {
        printf("Received command from client: %s\n", message.command);

        // 자식 프로세스 생성
        if (fork() == 0) {
            // 클라이언트 전용 파이프 열기
            snprintf(cli_pipe, sizeof(cli_pipe), "cli%s", message.pid);
            if ((cli_fd = open(cli_pipe, O_WRONLY)) == -1) {
                perror("open cli_pipe");
                exit(1);
            }

            // 표준 출력을 클라이언트 파이프로 리다이렉트
            close(1);         // 표준 출력 닫기
            dup(cli_fd);      // 파이프를 표준 출력으로 복사
            close(cli_fd);    // 파이프 닫기

            // 명령 실행
            execlp("/bin/sh", "sh", "-c", message.command, NULL);
            perror("execlp");
            exit(1);
        }

        // 부모 프로세스는 다른 요청 대기
        wait(NULL);
    }

    close(svr_fd);
    goto loop; // 무한 루프 유지

    unlink("SVR"); // 서버 종료 시 SVR 파이프 삭제
    return 0;
}

