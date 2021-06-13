#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	FILE* fp = fopen("my.bin","wb");

	if(fp == NULL){
		fprintf(stderr,"이진 파일 열기 실패\n");
		return 1;
	}

	int num1 = 140;
	fwrite(&num1, sizeof(int), 1, fp);
	 
	int num2 = 155;
	fwrite(&num2, sizeof(int), 1, fp);

	fclose(fp);

	fp = fopen("my.bin", "rb");

	if(fp == NULL){
		fprintf(stderr,"Error to open\n");
		return 1;
	}

	int num3 = 0;
	int num4 = 0;

	fread(&num3, sizeof(int), 1, fp);
	fread(&num4, sizeof(int), 1, fp);
	fclose(fp);

	printf("%d %d\n",num3,num4);

	return 0;
}
