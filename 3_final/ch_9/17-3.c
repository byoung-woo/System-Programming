#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *func(void *arg){ // Thread 함수 정의

	int *val = malloc(sizeof(int)); // 반환값 저장을 위한 동적 메모리
	
	*val = atoi((char*)arg);

	*val += 3;

	//return (void*)val;
	pthread_exit((void *) val); // 스레드의 반환값음 void*타입
}





int main(int argc, char *argv[]){

	if (argc < 4) {
        	fprintf(stderr, "Usage: %s 1 2 3\n", argv[0]);
        	exit(-1);
    	}

	int n = argc - 1;
	pthread_t t1[n];
	int *ret;

	// 각 입력값으로 스레드생성
	for(int i = 0;i < n;i++){
		if(pthread_create(&t1[i],NULL,func,argv[i + 1])!=0){
			perror("pthread_create(): ");
			exit(1);
		}
	}
	
	// 각 스레드 종료 대기 및 반환값 출력
	for(int j=0;j<n;j++){
		if(pthread_join(t1[j],(void**)&ret) != 0) { // pthread_join은 무조건 void** 타입을 기대함
			perror("pthread_join failed");
			exit(EXIT_FAILURE);
		}
		printf("pthread_exit=[%d]\n", *ret);
		free(ret);
	}

	return 0;

}

