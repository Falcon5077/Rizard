/*컴공창 파일복사 과제
	5532605 김형래
	2021.05.05
	복사할 파일을 읽어오고, 받을 파일을 한개 생성한다. 그리고 복사할 파일을 일정한 n값만큼 읽어 임시변수buf에 
	저장을 한 후 임시변수에 담긴 내용을 붙여넣을 파일에 쓴다. 이렇게 n값만큼 계속 읽고 쓰기를 반복하는데, 
	while문을 사용하여 복사할 파일의 끝까지, 즉 read함수가 리턴하는 값이 0이 될때까지 반복한다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUF_SIZE 1024

int main(int argc, char* argv[]){
	if(argc != 3){ //2개의 argument를 입력 못 받을시 문구 출력 후 프로그램종료
		printf("usage) %s source_flie target_file\n", argv[0]);
		return 0;
	}

	char buf[BUF_SIZE]; //읽은 데이터를 임시로 받아올 버퍼 변수
	int readd_size=0; // read함수가 반환하는 데이터 값(읽어온 데이터의 크기)을 저장할 변수

	int fd=open(argv[1], O_RDONLY); //첫번째 인자로 들어온 파일 오픈(읽기전용)
	if(fd<0){ //fd가 음수이면 에러
		fprintf(stderr, "Cannot open file %s", argv[1]);
		exit(-1);
	}

	int fd2=open(argv[2], O_CREAT | O_RDWR | O_EXCL, S_IRWXU);
	//두번째 인자로 들어온 파일명으로 새로운 파일 생성,owner에 읽기, 쓰기, 실행권한 모두 줌 
	if(fd2<0){ //fd2가 음수이면 에러
		fprintf(stderr, "Cannot open file %s", argv[2]);
		exit(-1);
	}

	while((readd_size=read(fd, buf, 4)))	{
		//fd가 가리키는 파일을 4바이트씩 읽어와서 임시변수 buf에 저장한다. 이를 파일 끝까지
		write(fd2, buf, readd_size); 
		//fd2가 가리키는 파일에 buf에 저장된 데이터의 크기만큼 buf에 저장된 내용을 쓴다.(저장)
	}

	close(fd); //fd사용종료
	close(fd2); //fd2사용종료

	return 0;
}
