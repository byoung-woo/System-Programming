#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// 스레드 함수 정의
void *thread_func(void *arg) {
    int val = atoi((char *)arg); // 입력값을 정수로 변환
    int *result = malloc(sizeof(int)); // 동적 메모리 할당
    if (result == NULL) { // 안써도 됨
        perror("malloc failed");
        pthread_exit(NULL);
    } 

    *result = val * val; // 제곱 계산
    pthread_exit((void *)result); // 결과 반환
}

int main(int argc, char *argv[]) {
    if (argc != 2) { // 입력값 확인
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        exit(1);
    }

    pthread_t thread; // 스레드 ID 변수
    int *result;      // 스레드 반환값 저장 포인터

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
    printf("Thread returned %d\n", *result);

    // 동적 메모리 해제
    free(result);

    return 0;
}

