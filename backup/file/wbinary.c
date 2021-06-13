#include <stdio.h>
#define SIZE 10

int main(void)
{
	int buf[SIZE];
	FILE *fp = NULL;
	int i;

	fp = fopen("binary.bin","rb");

	if(fp == NULL){
		fprintf(stderr,"error\n");
		return 1;
	}

	fread(buf,sizeof(int),SIZE,fp);

	for(i = 0; i <SIZE; i++)
		printf("%d", buf[i]);

	fclose(fp);

	return 0;
}

