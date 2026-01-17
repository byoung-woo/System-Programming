#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include "namedPipe.h"

int main(int argc, char *argv[]) {
    int fdpub, fdpriv;
    struct message msg;
    char line[LINESIZE];
    int n;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    // private FIFO 이름 설정
    sprintf(msg.privfifo, "Fifo%d", getpid());
    strcpy(msg.filename, argv[1]);

    // private FIFO 생성
    if (mknod(msg.privfifo, S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        exit(1);
    }

    // 서버의 public FIFO 열기
    if ((fdpub = open(PUBLIC, O_WRONLY)) == -1) {
        perror("open");
        exit(1);
    }

    // 서버로 요청 전송
    write(fdpub, (char *)&msg, sizeof(msg));
    close(fdpub);

    // private FIFO 열기
    if ((fdpriv = open(msg.privfifo, O_RDONLY)) == -1) {
        perror("open");
        unlink(msg.privfifo);
        exit(1);
    }

    // 서버로부터 데이터 수신
    while ((n = read(fdpriv, line, LINESIZE)) > 0) {
        write(STDOUT_FILENO, line, n);
    }

    close(fdpriv);

    return 0;
}

