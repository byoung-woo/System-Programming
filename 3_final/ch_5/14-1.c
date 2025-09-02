#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#define MAXLINE 1024

void signal_handler(int sig){

	if(sig==SIGINT){
		printf("SIGINT\n");
	}
	else if(sig==SIGQUIT){
		printf("end of session\n");
		exit(0);
	}
}

int main(){

	int status=0, pid;
	char line[MAXLINE]; //사용자의 입력을 받을 버퍼(배열)
	char *argv[MAXLINE/2];	//명령어를 인자별로 분리하기 위한 배열포인터
	char *path[] = {"/bin","/usr/bin","usr/local/bin",NULL}; // 명령이 있는 디렉토리를 정의하는 배열포인터
	char cmd[MAXLINE];	//실행시킬 명령어 배열
	
	signal(SIGINT,signal_handler);		
	signal(SIGQUIT,signal_handler);

	while(1){	
		
		printf("%%");
		//stdin으로부터 읽어서 line에 저장한다. MAXLINE은 최대 바이트수
		fgets(line,MAXLINE,stdin);	//fgets(char *str, int n, FILE *stream) -> 입력 스트림으로부터 문자열을 읽어들이기 위해 사용.
		
		line[strlen(line)-1] = '\0';	//문자열 끝에 개행문자를 넣기때문에 개행문자 제거를 위해 '\0'(NULL) 추가
		
		int argc = 0;
		// 아래 설명: line[MAXLINE] = "ls -a" 이렇게 들어와있다면 이 문자열을 띄어쓰기를 기준으로 자르는 작업
		argv[argc] = strtok(line," ");	//strtok로 line에있는 ls -a을 " "을 기준으로 자르자. 즉 공백을 기준으로 잘라서 argv[0]에 집어넣음->argv[0]에는 ls가 들어간다.
		while(argv[argc]!=NULL){ // argv[argc]가 NULL값이 아닐때까지. 즉 문자열의 끝까지 돌림
			argc++; // argv[1]로 만듬
			argv[argc] = strtok(NULL," "); //문자열의 다음 공백까지 찾고(strtok(NULL," ")) argv[1]에 넣는다. 즉 argv[1]에 -a이 들어감 
		}

		if(argc == 0){	//인자가 ls 이렇게 하나 들어오면 걍 continue
			continue;
			}
		
		if(strcmp(argv[0],"cd")==0){	// cd 구현
			chdir(argv[1]);
		}


		//명령어의 유무 판단 하는 로직
		int found = 0;
		for(int i=0;path[i]!=NULL;i++){	//path가 NULL이 아닐때까지 돌린다
			snprintf(cmd,sizeof(cmd),"%s/%s", path[i],argv[0]);	//cmd에 path[i]/argv[0](예를들어 ls) 저장
			if(access(cmd,X_OK)==0){	//예를들어 path[1]이 /bin이면 /bin/ls가 실행될 수 있는지 파악
				found = 1;	//있는 명령어다 -> found를 1로 바꿈
				break; //for문 탈출
			}
		}
		if(!found){	//다 돌렸는데 없다 -> found가 0이다 -> command not found 출력
			printf("command not found\n");
			continue;
		}
		
		pid = fork();	//프로세스를 실행시킬 자식 생성

		if(pid==0){	
			execv(cmd,&argv[0]);	//cmd에는 위에서 파악한 있는 명령어, 즉 /bin/ls가 들어있고 &argv[0]로 전체 명령어 가져옴 - argv라고 써도 됨(PPT배열포인터참고)
			exit(127);
		}
		
		wait(&status);	//자식 기다림
		if(status==0){	//성공적으로 종료되면 exit값 출력
			printf("child exit=[%x]\n",(status>>8));
		}
		else{	//그 외의 값이면 시그널처리
			printf("child signal=[%x]\n",(status>>8));
		}
}
}


