#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char  *argv[])
{
	char* fileName = "db.txt";
	unsigned char str;

	char len;
	unsigned char* arr;
	FILE *file = fopen(fileName,"wb");

	len = 8;
	fwrite(&len,1,sizeof(char),file);
	fwrite(&len,1,sizeof(char),file);
	fwrite(&len,1,sizeof(char),file);

	arr = "KKKMMMUUU___CCCSSS222666";
	fwrite(arr,strlen(arr),sizeof(unsigned char),file);

	len = 14;
	fwrite(&len,1,sizeof(char),file);
	fwrite(&len,1,sizeof(char),file);
	fwrite(&len,1,sizeof(char),file);

	arr = "HHHOOONNNGGG   CCCHHHAAANNN   PPPAAARRRKKK";
	fwrite(arr,strlen(arr),sizeof(unsigned char),file);

	return 0;
}

