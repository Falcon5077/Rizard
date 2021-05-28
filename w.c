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

void Read(char* tmp)
{
	FILE *file = fopen(tmp,"rb");

	char len[3];
	char m_len;
	unsigned char str[255] = " ";

	for(int t = 0; t < 3; t++){
		fread(&len[t],sizeof(char),1,file);
	}

	m_len = Check(&len[0]);
	printf("ID 길이 : %d\n",m_len);

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
	
	printf("ID : %s\n",str);

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
	
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


char Check(char* tmp)
{
	char real;

     if(tmp[0] != tmp[1])
     {
         if(tmp[0] != tmp[2])
         {
             if(tmp[1] == tmp [2])
             {
                 real = tmp[1];
             }
             else
             {
                 printf("셋다 틀림");
             }
         }
         else
         {
             real = tmp[0];
         }
     }
     else
     {
         real = tmp[0];
     }

	 return real;
}
