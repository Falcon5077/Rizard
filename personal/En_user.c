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
	FILE* fp = fopen("test_sample1.txt","rb");
	fp2 = fopen("q.bin","wb");
	
	char buffer[1000];
	char* line;
	int a = 0;
	int count = 0;
	
	while(!feof(fp)){
		line = fgets(buffer,1000,fp);
		if(strstr(line,"*")){		// a 1 user 2 item 3 ally 4 dis
			if( a == 1)
				break;
			printf("%d 번째 필드 \n",++a);
			continue;
		}	
		if(a ==1){
			char* value = strstr(line," ");
			count++;
			if(value != NULL){
				value[strlen(value)-1] = '\0';
				switch(count)
				{
					case 1:
						id = &value[1];
						idLen = strlen(id);
						WriteChar(idLen);
						WriteStr(idLen,id);
						break;
					case 2:
						name = &value[1];
						nameLen = strlen(name);
						WriteChar(nameLen);
						WriteStr(nameLen,name);
						break;
					case 3:
						if(value[1] == 'M')
						{
							gender = 'M';
							WriteChar(gender);
						}
						else if(value[1] == 'F'){
							gender = 'F';
							WriteChar(gender);
						}
						break;
					case 4:
						age = atoi(&value[1]);
						WriteChar(age);
						break;
					case 5:
						HP = atoi(&value[1]);
						WriteChar(HP);
						break;
					case 6:
						MP = atoi(&value[1]);
						WriteChar(MP);
						break;
					case 7:
						coin = atoi(&value[1]);
						WriteShort(coin);
						break;
				}	
			}
		}		
	}

	fclose(fp);
	
	return 0;
}
