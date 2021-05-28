#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Read(char* fileName);
char Check(char *len);

int main(int argc,char  *argv[])
{
	if(argc != 2)
	{
		printf("error\n");
		return 0;
	}

	Read(argv[1]);
}

void Read(char* tmp)	// Check 함수 먼저 읽으3
{
	FILE *file = fopen(tmp,"rb");

	char len[3];
	char m_len;
	unsigned char str[255] = " ";

	for(int t = 0; t < 3; t++){
		fread(&len[t],sizeof(char),1,file);	// ID길이 3개 읽어옴
	}

	m_len = Check(&len[0]);	// 읽어온 ID길이 3개를 Check 함수로 보내서 복원시킴 (667 을 보내면 6이 리턴됨)
	
	printf("ID 길이 : %d\n",m_len);

	for(int p = 0; p < m_len; p++)	// ID길이가 6이면 6번 반복 KKK MMM UUU ___ III DDD  <- 문자열 길이만큼 p 
	{
		char temp[3];
		for(int k = 0; k < 3; k++)	// 알파벳당 3번 저장하므로 3번 반복
		{
			fread(&temp[k],sizeof(unsigned char),1,file);	// 읽어온 알파벳을 temp[3]에 저장
		}

		char a = Check(&temp[0]);	// temp의 주소를 넣어서 읽어온 ID 중 p번째 알파벳 3개를 Check 함수로 보내서 복원시킴 (KKX 을 보내면 K가 리턴됨)
		str[p] = a;
	}
	
	printf("ID : %s\n",str);

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm	// 아래랑 같은맥락
	
	for(int t = 0; t < 3; t++){
      fread(&len[t],sizeof(char),1,file);
	}
	m_len = Check(&len[0]);
	printf("NAME 길이 : %d\n",m_len);
 
	for(int p = 0; p < m_len; p++)
	{
		char temp[3];
		for(int k = 0; k < 3; k++)
		{
			fread(&temp[k],sizeof(unsigned char),1,file);
		}
		
		char a = Check(&temp[0]);
		str[p] = a;
	}
	printf("NAME : %s\n",str);
	
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
