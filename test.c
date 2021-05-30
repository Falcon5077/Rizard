#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char  *argv[])
{
	char* fileName = "db.txt";
	unsigned char str;

	char len;
	unsigned char* arr;
	char test = '1' - 20;
	FILE *file = fopen(fileName,"wb");

	for(int i = 0; i < 10; i++){
		char tmp = '0' - 20 + i;
		fwrite(&tmp,1,sizeof(unsigned char),file);
	}

	fclose(file);

	file = fopen(fileName,"rb");

	for(int i = 0; i < 10; i++)
	{
		char tmp;
		fread(&tmp,1,sizeof(unsigned char),file);
		printf("0 - %d = %c , HEX : %d \n",20-i ,tmp,tmp);
	}

	return 0;
}

