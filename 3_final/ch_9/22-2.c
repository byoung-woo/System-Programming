#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// 스레드 함수 정의
void *thread_func(void *arg) {
    char *input = (char *)arg; // 전달받은 문자열
    printf("%s\n", input);     // 입력 문자열 출력

    int *length = malloc(sizeof(int)); // 문자열 길이를 저장할 동적 메모리 할당
    if (length == NULL) {
        perror("malloc failed");
        pthread_exit(NULL);
    }

    *length = strlen(input); // 문자열 길이 계산
    pthread_exit((void *)length); // 길이 반환
}

int main(int argc, char *argv[]) {
    if (argc != 2) { // 입력값 확인
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(1);
    }

    pthread_t thread; // 스레드 ID
    int *result;      // 스레드 반환값 저장

    // 스레드 생성
    if (pthread_create(&thread, NULL, thread_func, (void *)argv[1]) != 0) {
        perror("pthread_create failed");
        exit(1);
    }

    // 스레드 종료 대기 및 결과 수집
    if (pthread_join(thread, (void **)&result) != 0) {
        perror("pthread_join failed");
        exit(1);
    }

    // 결과 출력
    printf("%d\n", *result);

    // 동적 메모리 해제
    free(result);

    return 0;
}

