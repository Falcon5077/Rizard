#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_BUF 8192

int main(int argc, char* argv[])
{
	char buf[MAX_BUF];
	char* fileName = argv[2];

	if(argc != 3)
	{
		printf("다시 입력해주세요\n");
		return 0;
	}

	FILE *fp = fopen(fileName,"wt");
	if(fp == NULL){
		printf("파일생성 실패\n");
		return 0;
	}else
		printf("%s파일생성 성공\n",fileName);

	int fd = open(argv[1], O_RDONLY);
	if(fd < 0){
		fprintf(stderr, "Cannot open file %s\n",argv[1]);
		exit(-1);
	}

	int read_size = read(fd, buf, MAX_BUF);
	
	/*for(int i = 0; i < read_size; i++){
		fprintf(fp,"%c",buf[i]);
	}*/

	fd = open(argv[2], O_RDWR);

	int writen_size = write(fd,buf,read_size);
	printf("%s에 복사 완료!\n",fileName);

	close(fd);

	return 0;
}
