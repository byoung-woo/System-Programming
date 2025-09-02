#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include "namedPipe.h"

int main(int argc, char *argv[]) {
    int fdpub, fdpriv, fd, n, i;
    struct message msg;
    char line[LINESIZE];

    // "server"라는 이름의 FIFO 생성
    if (mknod(PUBLIC, S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        exit(1);
    }

    printf("Server is running...\n");

    // 서버의 public FIFO 열기
    if ((fdpub = open(PUBLIC, O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }

loop: // 반복을 위한 레이블
    while (read(fdpub, (char *)&msg, sizeof(msg)) > 0) {
        printf("Client Request Arrived: %s\n", msg.filename);

        // 요청된 파일 열기
        if ((fd = open(msg.filename, O_RDONLY)) == -1) {
            perror(msg.filename);
            continue;
        }

        // 클라이언트의 private FIFO 열기
        for (i = 0; i < NUMTRIES; i++) {
            if ((fdpriv = open(msg.privfifo, O_WRONLY | O_NDELAY)) == -1)
                sleep(1);
            else
                break;
        }

        if (fdpriv == -1) {
            perror(msg.privfifo);
            close(fd);
            continue;
        }

        // 파일 데이터를 클라이언트로 전송
        while ((n = read(fd, line, LINESIZE)) > 0) {
            write(fdpriv, line, n);
        }

        close(fd);
        close(fdpriv);
    }
    goto loop; // 반복을 위해 loop 레이블로 이동

    // 종료 시 public FIFO 삭제
    unlink(PUBLIC);
    return 0;
}

