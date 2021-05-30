#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* fName;
FILE *file;

char CheckChar(char* tmp)	// tmp 가 KKK 이면
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
				printf("셋다 틀림 ");
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

unsigned short CheckShort(unsigned short* tmp)		// tmp 가 KKK 이면
{
	unsigned short real;

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
				 printf("셋다 틀림 ");
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

char ReadLen()	// Check 함수 먼저 읽으
{
	char len[3];
	unsigned char m_len;

	for(int t = 0; t < 3; t++)
	{
		fread(&len[t],sizeof(unsigned char),1,file);	// ID길이 3개 읽어옴
	}
	m_len = Check(&len[0]);	// 읽어온 ID길이 3개를 Check 함수로 보내서 복원시킴 (667 을 보내면 6이 리턴됨)	

	return m_len;
}

unsigned short ReadShort()
{
	unsigned short len[3];
	unsigned short m_short;

	for(int t = 0; t<3; t++)
	{
		fread(&len[t],sizeof(unsigned short),1,file);
	}
	m_short = CheckShort(&len[0]);

	return m_short;
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

int main(int argc,char  *argv[])
{	
	if(argc != 2)
	{
		printf("Error\n");
		return 0;
	}

	fName = argv[1];
	file = fopen(fName,"rb");	// 입력받은 파일 open
	
	
	unsigned char tmpLen;		//문자열 길이를 받아올 변수

	printf("*User STATUS*\n");
	
	tmpLen = ReadLen();		// ID의 길이를 읽음
	ReadStr(tmpLen,"ID");		// ID길이만큼 ID 읽음

	tmpLen = ReadLen();		// 이름의 길이를 읽음
	ReadStr(tmpLen,"NAME");		// 이름의 길이만큼 이름을 읽음

	tmpLen = ReadLen();		// 성별을 읽고 출력함
	if(tmpLen == 'M')
		printf("GENDER: MALE\n");
	if(tmpLen == 'F')
		printf("GENDER: FEMALE\n");
	
	tmpLen = ReadLen();		// 나이를 읽고 출력함
	printf("AGE: %d\n",tmpLen);
	
	tmpLen = ReadLen();		// HP를 읽고 출력함
	printf("HP: %d\n",tmpLen);
	
	tmpLen = ReadLen();		// MP를 읽고 출력함
	printf("MP: %d\n",tmpLen);

	unsigned short tmp = ReadShort();	// Coin을 읽고 출력함
	printf("COIN: %d\n",tmp);
}
