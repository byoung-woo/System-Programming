#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Thread 함수 정의
void *thread_func(void *arg) {
    int argc = *(int *)arg;          // 전달받은 argc 값을 정수로 변환
    int *result = malloc(sizeof(int)); // 제곱값 저장을 위한 동적 메모리 할당
    if (result == NULL) {
        perror("malloc failed");
        pthread_exit(NULL);
    }

    *result = argc * argc; // argc 값의 제곱 계산
    pthread_exit((void *)result);    // 계산된 제곱값 반환
   // retunr (void*)result;
}

int main(int argc, char *argv[]) {
    pthread_t thread;               // 스레드 ID 저장 변수
    int *result;                    // Thread 반환값 저장 변수

    // Thread 생성
    if (pthread_create(&thread, NULL, thread_func, (void *)&argc) != 0) {
        perror("pthread_create failed");
        exit(1);
    }

    // Thread 종료 대기 및 반환값 수집
    if (pthread_join(thread, (void **)&result) != 0) {
        perror("pthread_join failed");
        exit(1);
    }

    // 반환값 출력
    printf("%d\n", *result);

    // 동적 메모리 해제
    free(result);

    return 0;
}

