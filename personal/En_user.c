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

int sort = 0;
int sortcheck = 0;
int bin = 0;

char* Items[] = {
	"BOMB",
	"POTION",
	"CURE",
	"BOOK",
	"SHIELD",
	"CANNON"
};
char* items1[7] = {0};
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

void WriteStr(unsigned char* str)
{
	unsigned char len = strlen(str);
	WriteChar(len);

	for(int i = 0; i < len; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			fwrite(&str[i],1,sizeof(unsigned char),fp2);
		}
	}
}

int CheckSeq(char* iname,char* value)
{	
	for(int i = 0; i < 6; i++)
	{
		if(strcmp(Items[i],iname) == 0){
			items1[i] = value;
			printf("%d번째 아이템 : %s개, \n",i,items1[i]);
			//WriteStr(items1[i]);
			switch(i){
				case 0:
					if(sortcheck > 0)
						sort = 1;
					sortcheck += 1;
					bin += 32;
					break;
				case 1:
					if(sortcheck > 1)
						sort = 1;
					sortcheck += 2;
					bin += 16;
					break;
				case 2:
					if(sortcheck > 3)
						sort = 1;
					sortcheck += 3;
					bin += 8;
					break;
				case 3:
					if(sortcheck > 6)
						sort = 1;
					sortcheck += 4;
					bin += 4;
					break;
				case 4:
					if(sortcheck > 10)
						sort = 1;
					sortcheck += 5;
					bin += 2;
					break;
				case 5:
					if(sortcheck > 15)
						sort = 1;
					sortcheck += 6;
					bin += 1;
					break;
			}

			return bin;
		}	
	}
}

void WriteItem()
{
}

int main(int argc,char *argv[])
{
	/*if(argc != 2)
	{
		printf("Error....\n");
		exit(1);
	}
	FILE* fp = fopen(argv[1],"rb");*/
	FILE* fp = fopen("test_sample1.txt","rb");
	fp2 = fopen("db.bin","wb");
	
	char buffer[1000];
	char* item_save[6];
	char* line;
	int a = 0;
	int count = 0;
	int count2 = 0;
	
	
	while(!feof(fp)){
		line = fgets(buffer,1000,fp);

		if(line == NULL){
			break;
		}
	
		if(strstr(line,"*")){		// a 1 user 2 item 3 ally 4 dis
			printf("%d 번째 필드! \n",++a);
			continue;
		}	
		if(a ==1){			
			char* value = strstr(line," ");
			if(value != NULL){
				value[strlen(value)-1] = '\0';	

				switch(++count)
				{
					case 1:
						id = &value[1];
						WriteStr(id);
						break;
					case 2:
						name = &value[1];
						WriteStr(name);
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
		else if(a == 2 )
		{
			char* field = strtok(line,":");
			char* value2 = strtok(NULL," ");
			if(value2 != NULL && field != NULL){
				++count2;
				value2[strlen(value2)-1] = '\0';
				CheckSeq(field,&value2[0]);
			}				
		}
	}

	fclose(fp);
//	printf("2진수 : %d \nSort : %d\n",bin,sort);

	for(int i = 0 ; i < 6; i++)
	{
		if(items1[i] != NULL)
		{	
		//	WriteStr(items1[i]);
			printf("%s : %s \n",Items[i],items1[i]);
			//printf("%s\n",items2[i]);
		}
	}

	if( sort == 0)
		printf("정렬됨 \n");
	else
		printf("정렬안됨\n");
//	fclose(fp);
	
	return 0;
}


