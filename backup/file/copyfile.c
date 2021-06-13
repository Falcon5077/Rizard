#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_BUF 8192
int main(int argc, char* argv[])
{
	
	char buf[MAX_BUF];			//8192 사이즈의 버퍼 생성
	char* fileName = argv[2];	//세번째 인자를 새로 생성할 파일 이름으로 선언

	if(argc != 3){	// 입력이 올바르지않으면 출력후 종료
		printf("usage) %s source_file target_file\n",argv[0]);
		return 0;
	}

	//file open
	FILE *targetFile = fopen(fileName,"wt");	
	FILE *sourceFile = fopen(argv[1],"rt");

	//오픈 실패시 출력
	if(targetFile == NULL || sourceFile == NULL)
	{
		printf("파일 생성 또는 읽기 실패\n");
		return -1;
	}
	else
		printf("파일 생성 성공\n");

	//source파일을 읽어서 버퍼에 저장
	int result = fread(buf,1,MAX_BUF,sourceFile);

	//저장된 버퍼를 target파일에 저장
	fwrite(buf,1,result,targetFile);
	
	//file close
	fclose(sourceFile);
	fclose(targetFile);

	return 0;
}
