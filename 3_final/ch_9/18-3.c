#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// 각 스레드가 수행할 함수
void *func(void *arg) {
    int val = atoi((char *)arg); // 입력 문자열을 정수로 변환
    sleep(1); // 1초 대기
    printf("%d\n", val * val); // 제곱값 출력
    pthread_exit(NULL); // 스레드 종료
}

int main(int argc, char *argv[]) {
    if (argc < 2) { // 입력값 검증
        fprintf(stderr, "Usage: %s <num1> <num2> ... <numN>\n", argv[0]);
        exit(1);
    }

    int n = argc - 1; // 생성할 스레드 개수
    pthread_t threads[n]; // 스레드 ID를 저장할 배열

    // 스레드 생성
    for (int i = 0; i < n; i++) {
        if (pthread_create(&threads[i], NULL, func, (void *)argv[i + 1]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    // 모든 스레드 종료 대기
    for (int i = 0; i < n; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    return 0; // main thread 종료
}

