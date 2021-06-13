#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE* fp = fopen("database.bin","rb");
	char buf[8192];
	int age;

	if(fp == 0)
	{
		return -1;
	}

	int num;
	while(feof(fp) == 0)
	{
		num = fread(buf,sizeof(int),1,fp);
		printf("%s",buf);
	}

	fclose(fp);

	return 0;

}
