#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char* fileName = "db.bin";
	unsigned char str;

	char len;
	unsigned char* arr;
	FILE* file = fopen(fileName, "wb");

	len = 8;
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);

	arr = "KKKMMMUUU___CCCSSS222333";
	fwrite(arr, strlen(arr), sizeof(unsigned char), file);

	len = 14;
	fwrite(&len, 1, sizeof(char), file);
	fwrite(&len, 1, sizeof(char), file);
	fwrite(&len, 1, sizeof(char), file);

	arr = "HHHOOONNNGGG   CCCHHHAAANNN   PPPAAARRRKKK";
	fwrite(arr, strlen(arr), sizeof(unsigned char), file);

	len = 'F';
	fwrite(&len, 1, sizeof(char), file);
	fwrite(&len, 1, sizeof(char), file);
	fwrite(&len, 1, sizeof(char), file);

	len = 33;
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);

	len = 200;
	fwrite(&len, 1, sizeof(char), file);
	fwrite(&len, 1, sizeof(char), file);
	fwrite(&len, 1, sizeof(char), file);

	len = 5;
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);

	unsigned short coin = 43210;
	fwrite(&coin, 1, sizeof(unsigned short), file);
	fwrite(&coin, 1, sizeof(unsigned short), file);
	fwrite(&coin, 1, sizeof(unsigned short), file);

	len = 1; // sort == 1
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);

	len = 3; // 아이템 갯수
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);

	len = 3; // 아이템유무를 이진수로 나타낸걸 10진수 변환한 값
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);

	len = 25; // 순서대로 갯수
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);

	len = 5; // 순서대로 갯수
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);

	len = 50; // 순서대로 갯수
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);

	len = 1; // 순서대로 갯수
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);

	len = 135; // 순서대로 갯수
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);
	return 0;
}