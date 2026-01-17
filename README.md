# 🐧 시스템 프로그래밍 (System Programming) 학습 및 실습 정리

이 저장소는 **리눅스 환경에서 시스템 프로그래밍 핵심 개념을 이해**하고, 저수준 인터페이스(System Call)를 활용해 다양한 기능을 구현한 실습 코드들을 모아둔 기록입니다.  
파일 입출력부터 프로세스 제어, 멀티스레딩까지 단계적으로 실습하며 정리했습니다.

---

## 🛠 기술 스택

- **Language:** C  
- **Environment:** Linux (WSL), GCC  
- **Key Concepts:** System Calls, File I/O, Signals, Pipes, FIFOs, Pthreads

---

## 📂 디렉토리 구조 및 주요 내용

### 1) 과제 및 기본 구현 (`1_assignment/`)
기본적인 시스템 유틸리티와 커스텀 셸 구현을 통해 시스템 호출의 흐름을 학습했습니다.

- **`myshell.c`**
  - `cd`, `gcc` 실행, `./a.out` 실행 및 `PATH` 환경 변수를 활용한 명령어 실행이 가능한 사용자 정의 셸
- **`pipeclient.c` / `pipeserver.c`**
  - Named Pipe(FIFO)를 이용한 기본적인 클라이언트-서버 통신 구조
- **`2-1.c ~ 2-3.c`**
  - `lseek`를 활용한 파일 역순 복사
  - 파일 데이터 건너뛰며 읽기 등 파일 포인터 조작 실습

---

### 2) 중간고사 대비 실습 (`2_middle/`)
파일 기술자(File Descriptor) 조작과 리다이렉션의 기초를 다졌습니다.

- **파일 조작 및 변환**
  - 문자열의 아스키 코드 합 계산(`15_1.c`)
  - 파일 내 특정 위치 데이터 수정(`15_2.c`)
  - 3바이트씩 시프트하여 암호화된 파일 생성(`11_2.c`) 등
- **입출력 리다이렉션**
  - `dup2`를 사용하여 표준 입출력을 파일로 변경
  - 파일 내용을 화면에 출력하거나 파일끼리 복사하는 기능 실습
- **데이터 검색**
  - 파일 내 특정 단어 출현 횟수 카운트 기능 구현

---

### 3) 기말고사 및 심화 주제 (`3_final/`)

#### 3-1) 시그널 제어 (`ch_5_signal/`)
프로세스 간 비동기 이벤트 전달 및 예외 처리를 학습했습니다.

- **타이머 및 알람**
  - `setitimer`, `alarm`을 활용한 타임아웃 처리
  - 자식 프로세스 실행 시간 제한 기능 구현
- **핸들러 등록**
  - `SIGINT(Ctrl+C)`, `SIGQUIT` 등 시그널을 가로채 사용자 정의 동작 수행

#### 3-2) 파이프 및 통신 (`ch_6_pipe/`, `ch_6_server_client/`)
프로세스 간 데이터 교환 기법을 상세히 다루었습니다.

- **Anonymous Pipe**
  - `pipe()`로 부모-자식 간 파이프 구성
  - `ls | grep` 같은 파이프라인 형태 구현
- **Named Pipe (FIFO) Server-Client**
  - Public FIFO로 요청 수신 → Private FIFO(PID 기반)로 1:1 응답
  - 클라이언트가 보낸 셸 명령어를 서버에서 실행 후 결과를 다시 전송

#### 3-3) 멀티스레딩 (`ch_9/`)
`pthread` 기반 병렬 처리를 학습했습니다.

- **스레드 생성 및 종료**
  - `pthread_create`로 생성, `pthread_join`으로 종료 대기 및 자원 회수
- **데이터 전달 및 반환**
  - 스레드 함수 인자 전달
  - 실행 결과(예: 제곱값, 문자열 길이)를 `malloc`으로 동적 할당해 메인 스레드로 반환

---

## 🚀 실행 방법

### 1) 기본 컴파일
```bash
gcc -o output_name filename.c
./output_name
```

### 2) 스레드(pthread) 코드 컴파일
```bash
gcc -o output_name filename.c -lpthread
./output_name
```

### 3) 서버-클라이언트 실습 (FIFO)
- 서버 실행
```bash
gcc -o server 11-4-server.c
./server
```

- 클라이언트 실행
```bash
gcc -o client 11-4-client.c
./client <파일명>
```

---