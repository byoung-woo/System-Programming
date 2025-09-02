#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include "namedPipe.h"

int main() {
    struct message msg;
    char line[LINESIZE];
    int server_fd, client_fd, n;

    while (1) {
        printf("shell> ");
        fflush(stdout);

        // 사용자 입력 받기
        if (fgets(msg.filename, sizeof(msg.filename), stdin) == NULL) {
            continue; // 입력 오류 시 루프 반복
        }

        // 줄바꿈 문자 제거
        msg.filename[strcspn(msg.filename, "\n")] = '\0';

        // 종료 명령 처리
        if (strcmp(msg.filename, "exit") == 0) {
            printf("Exiting shell...\n");
            break;
        }

        // Private FIFO 이름 설정
        sprintf(msg.privfifo, "FIFO%d", getpid());

        // Private FIFO 생성
        if (mknod(msg.privfifo, S_IFIFO | 0666, 0) == -1) {
            perror("mknod");
            continue;
        }

        // Public FIFO 열기
        if ((server_fd = open(PUBLIC, O_WRONLY)) == -1) {
            perror("open PUBLIC");
            unlink(msg.privfifo);
            continue;
        }

        // 서버로 요청 전송
        write(server_fd, &msg, sizeof(msg));
        close(server_fd);

        // Private FIFO 열기
        if ((client_fd = open(msg.privfifo, O_RDONLY)) == -1) {
            perror("open CLIENT FIFO");
            unlink(msg.privfifo);
            continue;
        }

        // 서버로부터 결과 수신 및 출력
        while ((n = read(client_fd, line, LINESIZE)) > 0) {
            write(STDOUT_FILENO, line, n);
        }

        close(client_fd);
        unlink(msg.privfifo); // Private FIFO 삭제
    }

    return 0;
}

