#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char idLen;
unsigned char id[255];

unsigned char nameLen;
unsigned char name[255];

unsigned char genderLen;
unsigned char gender[255];

unsigned char age;
unsigned char age_u[255];

unsigned char HP;
unsigned char HP_u[255];

unsigned char MP;
unsigned char MP_u[255];

unsigned short coin;
unsigned char coin_u[255];



FILE *fp2;

void WriteChar(unsigned char len) {

	for(int i = 0; i < 3; i++)
		fwrite(&len,1,sizeof(unsigned char),fp2);

}

void WriteShort(unsigned short s_len) {

	for(int i = 0; i < 3; i++)
		fwrite(&s_len,1,sizeof(unsigned short),fp2);

}

void WriteStr(unsigned char len,unsigned char* str) {

	for(int i = 0; i < len; i++) {

		for(int j = 0; j < 3; j++) {

			fwrite(&str[i],1,sizeof(unsigned char),fp2);

		}
	}
}


void read(){

	unsigned char user_buff[1000] = "KMU_CS23\nHONG CHAN PARK\nF\n20\n200\n5\n43210\n";
	unsigned char *temp;

	temp = strtok(user_buff, "\n");
	strcpy(id, temp);

	temp = strtok(NULL, "\n");
	strcpy(name, temp);

	temp = strtok(NULL, "\n");
	strcpy(gender, temp);

	temp = strtok(NULL, "\n");
	strcpy(age_u, temp);
	age = atoi(age_u);

	temp = strtok(NULL, "\n");
	strcpy(HP_u, temp);
	HP = atoi(HP_u);

	temp = strtok(NULL, "\n");
	strcpy(MP_u, temp);
	MP = atoi(MP_u);

	temp = strtok(NULL, "\n");
	strcpy(coin_u, temp);
	coin = atoi(coin_u);

}

void Write(){

	idLen = strlen(id);
	nameLen = strlen(name);
  genderLen = strlen(gender);

	WriteChar(idLen);
	WriteStr(idLen,id);

	WriteChar(nameLen);
	WriteStr(nameLen,name);

	WriteChar(genderLen);
	WriteStr(genderLen, gender);

	WriteChar(age);

	WriteChar(HP);
	WriteChar(MP);

	WriteShort(coin);

}

int main(int argc,char *argv[]) {

	fp2 = fopen("usertest1.bin","wb");

	read();
	Write();

	return 0;
}
