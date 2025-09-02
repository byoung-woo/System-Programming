#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#define MAXLINE 1024

void signal_handler(int sig) {
    if (sig == SIGINT) {
        printf("\nSIGINT\n");
    } else if (sig == SIGQUIT) {
        printf("\nend of session\n");
        exit(0);
    }
}

int main() {
    int status = 0, pid;
    char line[MAXLINE];        // 사용자 입력 버퍼
    char *argv[MAXLINE / 2];   // 명령어를 인자별로 분리하기 위한 배열
    char *path[] = {"/bin", "/usr/bin", "/usr/local/bin", NULL}; // 명령 경로
    char cmd[MAXLINE];         // 실행 명령어

    // 시그널 처리기 등록
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);

    while (1) {
        printf("%% "); // 프롬프트 출력
        fflush(stdout);

        // 사용자 입력 받기
        if (fgets(line, MAXLINE, stdin) == NULL) {
            continue; // 입력이 없으면 루프 재시작
        }

        line[strlen(line) - 1] = '\0'; // 개행 문자 제거

        int argc = 0;
        argv[argc] = strtok(line, " "); // 입력 문자열 분리
        while (argv[argc] != NULL) {
            argc++;
            argv[argc] = strtok(NULL, " ");
        }

        if (argc == 0) { // 빈 명령어 처리
            continue;
        }

        // `cd` 명령어 처리
        if (strcmp(argv[0], "cd") == 0) {
            if (argc < 2) {
                printf("cd: missing argument\n");
            } else if (chdir(argv[1]) != 0) {
                perror("cd error");
            }
            continue;
        }

        // 명령어 유효성 검사
        int found = 0;
        for (int i = 0; path[i] != NULL; i++) {
            snprintf(cmd, sizeof(cmd), "%s/%s", path[i], argv[0]);
            if (access(cmd, X_OK) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) { // 명령어가 존재하지 않는 경우
            printf("command not found\n");
            continue;
        }

        // 자식 프로세스 생성 및 명령 실행
        pid = fork();
        if (pid < 0) {
            perror("fork error");
            continue;
        }

        if (pid == 0) { // 자식 프로세스
            execv(cmd, argv); // 명령 실행
            perror("execv failed"); // execv 실패 시 에러 출력
            exit(127);
        }

        // 부모 프로세스: 자식 종료 대기
        if (wait(&status) < 0) {
            perror("wait error");
            continue;
        }

        // 종료 상태 확인
        if (WIFEXITED(status)) {
            printf("child exit=[%x]\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("child signal=[%x]\n", WTERMSIG(status));
        }
    }

    return 0;
}

