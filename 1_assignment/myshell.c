#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#define MAX_PATH 256

int main(){
	char line[256], *pathPtr[MAX_PATH];
	char path[100][256];
	char buf[256];

	int count=0;
	int fd;

	if((fd=open("./PATH", O_RDONLY))<0){
		perror("PATH 읽기X");
		exit(1);
	}

	ssize_t size=read(fd, buf, sizeof(buf) -1);
	if(size<0){
		perror("읽기X");
		close(fd);
		exit(1);
	}

	buf[size]='\0';
	close(fd);

	char *ptr=strtok(buf, "\n");
	while(ptr != NULL){
		if(strncmp(ptr, "PATH=", 5)==0){
			char *token=strtok(ptr + 5, ":");
			while(token != NULL && count < MAX_PATH){
				strncpy(path[count], token, 255);
				path[count][255] = '\0';
				pathPtr[count]=path[count];
				count++;
				token=strtok(NULL, ":");
			}
		}
		ptr=strtok(NULL, "\n");
	}

	signal(SIGINT, SIG_IGN);

	while(1){
		fprintf(stderr, "command: ");
		fflush(stderr);

		if(fgets(line, sizeof(line), stdin)==NULL){
			break;
		}

		line[strcspn(line, "\n")]='\0';

		if(line[0]=='\0'){
			continue;
		}

		if(strncmp(line, "cd ", 3)==0){
			char *dir = line+3;
			if(chdir(dir) != 0){
				perror("디렉토리를 변경X ");
			}
			continue;
		}

		if(strncmp(line, "gcc ", 4)==0){
			pid_t pid=fork();
			if(pid<0){
				perror("fork fail");
				exit(1);
			}
			if(pid==0){
				char *argv[256];
				int i=0;
				argv[i]=strtok(line, " ");
				while(argv[i] != NULL){
					argv[++i]=strtok(NULL, " ");
				}
				execvp("gcc", argv);
				perror("gcc fail");
				exit(1);
			}
			else{
				int status;
				waitpid(pid, &status, 0);
			}
			continue;
		}

		if(strcmp(line, "./a.out")==0){
			if(access("./a.out", X_OK) != 0){
				perror("a.out이 존재하지 않습니다.");
				continue;
			}
			pid_t pid=fork();
			if(pid<0){
				perror("Fork fail");
				exit(1);
				}
			if(pid==0){
				char *argv[] = {"./a.out", NULL};
				execv("./a.out", argv);
				perror("./a.out fail");
				exit(1);
			}
			else{
				int status;
				waitpid(pid, &status, 0);
			}
			continue;
		}

		char *argv[256];
		int i=0;
		argv[i]=strtok(line, " ");
		while(argv[i] != NULL){
			argv[++i]=strtok(NULL, " ");
		}

		char fpath[256];
		int found=0;
		for (int j=0; j<count; j++){
			snprintf(fpath, sizeof(fpath), "%s/%s", pathPtr[j], argv[0]);
			if(access(fpath, X_OK)==0){
				found=1;
				break;
			}
		}
		if(found){
			pid_t pid=fork();
			if(pid<0){
				perror("Fork fail");
				exit(1);
			}
			if(pid==0){
				execv(fpath, argv);
				perror("execv fail");
				exit(1);
			}
			else{
				int status;
				waitpid(pid, &status, 0);
			}
		}
		else{
			printf("Command not found\n");
		}
	}
	return 0;
}
