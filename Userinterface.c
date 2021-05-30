#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ReadLen(char* target);
unsigned short ReadShort();
void ReadStr(char len,char* target);
char Check(char *len);

char* fName;
FILE *file;

int main(int argc,char  *argv[])
{
	unsigned char tmpLen;
	
	if(argc != 2)
	{
		printf("error\n");
		return 0;
	}

	fName = argv[1];
	file = fopen(fName,"rb");

	printf("*User STATUS*\n");
	tmpLen = ReadLen("ID");
	ReadStr(tmpLen,"ID");

	tmpLen = ReadLen("Name");
	ReadStr(tmpLen,"Name");

	tmpLen = ReadLen("Gender");
	if(tmpLen == 'M')
		printf("Gender: Male\n");
	if(tmpLen == 'F')
		printf("Gender: Female\n");
	
	tmpLen = ReadLen("나이");
	printf("AGE: %d\n",tmpLen);
	tmpLen = ReadLen("HP");
	printf("HP: %d\n",tmpLen);
	tmpLen = ReadLen("MP");
	printf("MP: %d\n",tmpLen);

	ReadShort();
}

char ReadLen(char* target)	// Check 함수 먼저 읽으3
{
	char len[3];
	unsigned char m_len;

	for(int t = 0; t < 3; t++){
		fread(&len[t],sizeof(unsigned char),1,file);	// ID길이 3개 읽어옴
	}

	m_len = Check(&len[0]);	// 읽어온 ID길이 3개를 Check 함수로 보내서 복원시킴 (667 을 보내면 6이 리턴됨)	

	return m_len;
}

unsigned short ReadShort()
{
	char len[3];
	unsigned short m_short;

	fread(&m_short,sizeof(unsigned short),1,file);
	printf("%d",m_short);
/*
	for(int t = 0; t<3; t++)
	{
		fread(&len[t],sizeof(unsigned short),1,file);
	}
	m_short = Check(&len[0]);

	return m_short;*/
}

void ReadStr(char len, char* target)
{
	unsigned char str[255] = " ";

	for(int p = 0; p < len; p++)
	{
		char temp[3];
		for(int k = 0; k < 3; k++)
		{
			fread(&temp[k],sizeof(unsigned char),1,file);
		}
		char a = Check(&temp[0]);
		str[p] = a;
	}

	printf("%s: %s\n",target,str);
}

char Check(char* tmp)		// tmp 가 KKK 이면
{
	char real;

     if(tmp[0] != tmp[1])	// tmp[0] K랑 tmp[1] K가 같은지 비교
     {
         if(tmp[0] != tmp[2])	// 0이랑 1이 틀다면 0이랑 2가 같은지 비교
         {
             if(tmp[1] == tmp [2])	// 같다면 1이랑 2, 2개가 같기때문에
             {
                 real = tmp[1];	// real에 tmp중 1이나 2 아무거나 넣어서 리턴	(XKK) 의 경우
             }
             else
             {
                 printf("셋다 틀림");
             }
         }
         else	// 0이랑 2가 같다면 real에 0을 넣어서 리턴 (KXK) 의 경우
         {
             real = tmp[0];
         }
     }
     else
     {
         real = tmp[0];	// 0이랑 1이 같으니 (KKX)의 경우
     }

	 return real;
}
