#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

struct msg {
    char pid[50];
    char command[100];
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(1);
    }

    struct msg message;
    int svr_fd, cli_fd;
    char cli_pipe[64], line[256];

    // 메시지 작성
    snprintf(message.pid, sizeof(message.pid), "%d", getpid());
    snprintf(message.command, sizeof(message.command), "%s", argv[1]);
    for (int i = 2; i < argc; i++) {
        strncat(message.command, " ", sizeof(message.command) - strlen(message.command) - 1);
        strncat(message.command, argv[i], sizeof(message.command) - strlen(message.command) - 1);
    }

    // 클라이언트 전용 파이프 생성 (mknod 사용)
    snprintf(cli_pipe, sizeof(cli_pipe), "cli%s", message.pid);
    if (mknod(cli_pipe, S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        exit(1);
    }

    // SVR 파이프 열기
    if ((svr_fd = open("SVR", O_WRONLY)) == -1) {
        perror("open SVR");
        unlink(cli_pipe);
        exit(1);
    }

    // 서버로 메시지 전송
    write(svr_fd, &message, sizeof(message));
    close(svr_fd);

    // 클라이언트 전용 파이프 열기 및 서버 응답 대기
    if ((cli_fd = open(cli_pipe, O_RDONLY)) == -1) {
        perror("open cli_pipe");
        unlink(cli_pipe);
        exit(1);
    }

    // 서버 응답 읽기
    while (read(cli_fd, line, sizeof(line)) > 0) {
        write(STDOUT_FILENO, line, strlen(line)); // 화면에 출력
    }

    close(cli_fd);
    unlink(cli_pipe); // 파이프 삭제
    return 0;
}

