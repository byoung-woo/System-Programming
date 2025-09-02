#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// 스레드 함수 정의
void *thread_func(void *arg) {
    int val = atoi((char *)arg); // 입력값을 정수로 변환
    int *result = malloc(sizeof(int)); // 동적 메모리 할당
    if (result == NULL) {//오류제어 굳이필요없음
        perror("malloc failed");
        pthread_exit(NULL);
    }
    sleep(1);
    *result = val * val; // 제곱 계산
    pthread_exit((void *)result); // 결과 반환
}

int main(int argc, char *argv[]) {
    if (argc < 2) { // 최소 하나 이상의 입력값 확인
        fprintf(stderr, "Usage: %s <number1> <number2> ... <numberN>\n", argv[0]);
        exit(1);
    }

    int n = argc - 1;           // 입력값 개수
    pthread_t threads[n];       // 스레드 ID 배열
    int *results[n];            // 결과 저장 배열

    // 스레드 생성
    for (int i = 0; i < n; i++) {
        if (pthread_create(&threads[i], NULL, thread_func, (void *)argv[i + 1]) != 0) {
            perror("pthread_create failed");
            exit(1);
        }
    }

    // 스레드 종료 대기 및 결과 수집
    for (int i = 0; i < n; i++) {
        if (pthread_join(threads[i], (void **)&results[i]) != 0) {
            perror("pthread_join failed");
            exit(1);
        }
	printf("Input: %s, Result: %d\n", argv[i + 1], *results[i]);
        free(results[i]); // 동적 메모리 해제
    }

    return 0;
}

