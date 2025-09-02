
#include "namedPipe_13.h"

int main(int argc, char *argv[]) {
    struct msg msg;
    char line[LINESIZE];
    int server_fd, client_fd, n;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(1);
    }

    // Private FIFO 이름 설정
    sprintf(msg.pipe, "FIFO%d", getpid());

    // 명령어 구성
    snprintf(msg.command, sizeof(msg.command), "%s", argv[1]);
    for (int i = 2; i < argc; i++) {
        strncat(msg.command, " ", sizeof(msg.command) - strlen(msg.command) - 1);
        strncat(msg.command, argv[i], sizeof(msg.command) - strlen(msg.command) - 1);
    }

    // Private FIFO 생성
    if (mknod(msg.pipe, S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        exit(1);
    }

    // Public FIFO 열기
    if ((server_fd = open(PUBLIC, O_WRONLY)) == -1) {
        perror("open public fifo");
        unlink(msg.pipe);
        exit(1);
    }

    // 서버로 요청 전송
    write(server_fd, &msg, sizeof(msg));
    close(server_fd);

    // Private FIFO 열기
    if ((client_fd = open(msg.pipe, O_RDONLY)) == -1) {
        perror("open private fifo");
        unlink(msg.pipe);
        exit(1);
    }

    // 서버 응답 읽기 및 출력
    while ((n = read(client_fd, line, LINESIZE)) > 0) {
        write(STDOUT_FILENO, line, n);
    }

    close(client_fd);
    unlink(msg.pipe);
    return 0;
}

