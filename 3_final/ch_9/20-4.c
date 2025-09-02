#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// 스레드 함수 정의
void *thread_func(void *arg) {
    printf("This is thread\n");
    sleep(1); // 1초 대기
    pthread_exit(NULL); // 스레드 종료 // 단일 스레드에서는 exit가 굳이 필요하지 않지만 다중 스레드를 사용할때는 exit가 필요하다 사용하는 습관을 길러두자
}

int main() {
    pthread_t thread; // 스레드 ID 변수

    // 스레드 생성
    if (pthread_create(&thread, NULL, thread_func, NULL) != 0) {
        perror("pthread_create failed");
        exit(1);
    }

    // 스레드 종료 대기
    if (pthread_join(thread, NULL) != 0) {
        perror("pthread_join failed");
        exit(1);
    }

    // 스레드 종료 후 출력
    printf("OK\n");

    return 0;
}

