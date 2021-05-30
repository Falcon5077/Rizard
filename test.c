#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char* fileName = "db.bin";
	unsigned char str;

	char len;
	FILE* file = fopen(fileName, "wb");

	len = 1;
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);

	len = 3;
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);

	len = 5;
	fwrite(&len, 1, sizeof(char), file);
	fwrite(&len, 1, sizeof(char), file);
	fwrite(&len, 1, sizeof(char), file);

	len = 5;
	fwrite(&len, 1, sizeof(char), file);
	fwrite(&len, 1, sizeof(char), file);
	fwrite(&len, 1, sizeof(char), file);

	len = 1;
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);

	len = 1;
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);
	fwrite(&len, 1, sizeof(unsigned char), file);
	
		len = 2;
		fwrite(&len, 1, sizeof(unsigned char), file);
		fwrite(&len, 1, sizeof(unsigned char), file);
		fwrite(&len, 1, sizeof(unsigned char), file);

		len = 3;
		fwrite(&len, 1, sizeof(unsigned char), file);
		fwrite(&len, 1, sizeof(unsigned char), file);
		fwrite(&len, 1, sizeof(unsigned char), file);

	fclose(file);

	return 0;
}
