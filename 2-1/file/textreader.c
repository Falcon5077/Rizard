#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_BUF 1024

int main(int argc, char* argv[]) {
	char buf[MAX_BUF];
	int in, out;
	int storage;
	
	if(argc!=3) //argc가 3개가 아닐경우 즉, 실행파일과 복사할피알, 붙여넣을 파일명이 입력되지 않았을 경우
		printf("Usage) ./copy.out source_file target_file\n"); //오류메시지 출력
	
	in = open(argv[1], O_RDONLY);	//in함수에 1번째argv(복사할 파일)을 open해 저장한다.
	out = open(argv[2], O_CREAT|O_WRONLY|O_EXCL, 0744);
	//out에 복사된 파일을 붙여넣기 할 argv[2]에 들어온 이름의 파일을 만든다.
	
	//in에 저장된 파일에서 MAX_BUF크기의 바이트를 읽어서 buf함수에 저장하고, 읽은 바이트를 리턴해 storage함수에 저장한다.
	while((storage = read(in, buf, MAX_BUF)) > 0)	//while이 더이상 읽을값이 없어 read가 -1(0보다 작은값)을 return할때까지 반복한다.
		write(out, buf, storage); 
		//반복 할 때 마다read를 통해 storage에 저장된 바이트값을 out에 저장된 파일에 쓴다.

	return 0;
}
