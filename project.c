#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct {
	unsigned char I_length;
	unsigned char N_length;
	char ID[255];
	char name[255];
	char gender;
	char age;
	char buffer [1000];
	char buffer_n[1000];
	char buffer_g[3];
	char buffer_age[3];
}info; // 동맹 구조체

info FRIEND[100]; //동맹 배열

char* fName;
FILE *file;

unsigned char num; // 동맹수

char checkChar(char *tmp)
{
	char real;

	if(tmp[0] != tmp[1])
	{
		if(tmp[0] != tmp[2])
		{
			if(tmp[1] == tmp[2]) 
			{
				real = tmp[1];
			}
			else 
			{
				printf("셋다 틀림 ");
				real = tmp[2];
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

char ReadLen()
{
	char len[3];
	unsigned char m_len;

	for(int t = 0; t < 3; t++)
	{
		fread(&len[t],sizeof(unsigned char),1,file);
	}
	m_len = checkChar(&len[0]);
	
	return m_len;
}

void Checkstr_I(char *buffer,int F_num) {
	char tmp[3];
	int index = 0;
	for(int i = 0; buffer[i] !=0; i = i + 3) {
			tmp[0] = buffer[i];
			tmp[1] = buffer[i+1];
			tmp[2] = buffer[i+2];
			FRIEND[F_num].ID[index]= checkChar(tmp);
			index++;
	}
} //ID buffer에 저장된 데이터를 추출한다.

void Checkstr_N(char *buffer,int F_num) {
	char tmp[3];
	int index = 0;
	for(int i =0; buffer[i] !=0; i = i+3) {
		tmp[0] = buffer[i];
		tmp[1] = buffer[i+1];
		tmp[2] = buffer[i+2];
		FRIEND[F_num].name[index] = checkChar(tmp);
		index++;
	}
} //name buffer에 저장된 데이터를 추출한다.

void FRIEND_READ() { // 인코더 파일 읽어오는 함수
	num = ReadLen(); // 동맹수를 읽어 온다.
	int x = 0;
	for(int i = 0; i < num; i++) {
		FRIEND[i].I_length = ReadLen();
		fread(FRIEND[i].buffer,sizeof(char), FRIEND[i].I_length * 3 ,file);
		FRIEND[i].N_length = ReadLen();
		fread(FRIEND[i].buffer_n,sizeof(char), FRIEND[i].N_length *3 ,file);
		fread(FRIEND[i].buffer_g,sizeof(char),3,file);
		fread(FRIEND[i].buffer_age,sizeof(char),3,file);
	}	
}

void FRIEND_SAVE() { // buffer에 있는 정보를 걸러서 출력하고자하는 구조체에 저장
	for(int i = 0; i < 3; i++) {
		Checkstr_I(FRIEND[i].buffer,i);
		Checkstr_N(FRIEND[i].buffer_n,i);
		FRIEND[i].gender = checkChar(FRIEND[i].buffer_g);
		FRIEND[i].age = checkChar(FRIEND[i].buffer_age);	
	}
}

void print() {
	printf("*FRIENDS LIST*\n");
	for(int i = 0; i< num; i++) {
		printf("ID : %s\n",FRIEND[i].ID);
		printf("NAME : %s\n",FRIEND[i].name);
		if(FRIEND[i].gender=='M') {
			printf("GENDER : MALE\n");
		}
		else {
			printf("GENDER : FEMALE\n");
		}
		printf("AGE : %d\n\n",FRIEND[i].age);
	}
}

void fprint(char *file) {
	FILE *fp = fopen(file,"w");
	fprintf(fp,"*FRIENDS LIST*\n");
	for(int i = 0; i<num; i++) {
		fprintf(fp,"FRIEND%d ID: %s\n",i+1,FRIEND[i].ID);
		fprintf(fp,"FRIEND%d NAME: %s\n",i+1,FRIEND[i].name);
		if(FRIEND[i].gender=='M') {
			fprintf(fp,"FRIEND%d GENDER: MALE\n",i+1);
		}
		else {
			fprintf(fp,"FRIEND%d GENDER: FEMALE\n",i+1);
		}
		fprintf(fp,"FRIEND%d AGE : %d\n\n",i+1,FRIEND[i].age);
	}
}

int main(int argc,char *argv[]) {
	if(argc != 3) {
		fprintf(stderr,"오류");
		exit(1);
	}

	fName = argv[1];
	file = fopen(fName,"rb");

	FRIEND_READ();
	FRIEND_SAVE();
	print();
	fprint(argv[2]);
	return 0;
}
