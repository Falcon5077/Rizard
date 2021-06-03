#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char idLen;
unsigned char *id;
unsigned char nameLen;
unsigned char *name;
unsigned char gender;
unsigned char age;
unsigned char HP;
unsigned char MP;
unsigned short coin;

FILE *fp2;

void WriteChar(unsigned char len)
{
	for(int i = 0; i < 3; i++)
		fwrite(&len,1,sizeof(unsigned char),fp2);
}
void WriteShort(unsigned short s_len)
{
	for(int i = 0; i < 3; i++)
		fwrite(&s_len,1,sizeof(unsigned short),fp2);
}

void WriteStr(unsigned char len,unsigned char* str)
{
	for(int i = 0; i < len; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			fwrite(&str[i],1,sizeof(unsigned char),fp2);
		}
	}
}

int main(int argc,char *argv[])
{
	fp2 = fopen("q.bin","wb");
	// fread로 각 변수에 저장
	id = "KMU_CS23";
	name = "HONG CHAN PARK";
	gender = 'F';
	age = 33;
	HP = 200;
	MP = 5;
	coin = 43210;

	idLen = strlen(id);
	nameLen = strlen(name);

	WriteChar(idLen);
	WriteStr(idLen,id);

	WriteChar(nameLen);
	WriteStr(nameLen,name);

	WriteChar(gender);
	WriteChar(age);
	WriteChar(HP);
	WriteChar(MP);

	WriteShort(coin);

	

}
