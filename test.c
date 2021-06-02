#include <stdio.h>
#include <string.h>
typedef struct {
	char ID[255];
	char name[255];
	char gender;
	char age;
	unsigned char I_length;
	unsigned char N_length;
}info;

FILE *fp;
info friend[100];
unsigned char num = 3;

void f_write() {
	for(int i = 0; i < 3; i++) {
		fwrite(&num,sizeof(unsigned char),1,fp);
	}
}

void w_length(unsigned char length) {
	for(int i = 0; i < 3; i++) {
		fwrite(&length,sizeof(unsigned char),1,fp);
	}
}

void w_gn(char c) {
	for(int i = 0; i < 3; i++) {
		fwrite(&c,sizeof(char),1,fp);
	}
}

void write() {
	f_write();
	for(int i = 0; i < num; i++) {
		w_length(friend[i].I_length);
		fwrite(friend[i].ID,sizeof(char),strlen(friend[i].ID),fp);
		w_length(friend[i].N_length);
		fwrite(friend[i].name,sizeof(char),strlen(friend[i].name),fp);
		w_gn(friend[i].gender);
		w_gn(friend[i].age);
	}
}

int main() {
	fp = fopen("project.bin","wb");
	strcpy(friend[0].ID,"KKKMMMUUU____CCCSSS111");
	strcpy(friend[0].name,"KKKIIIMMM   SSS");
	friend[0].gender = 'M';
	friend[0].age = 22;
	friend[0].I_length = 7;
	friend[0].N_length = 5;

	strcpy(friend[1].ID,"KKKMMMUUU___CCCSSS222");
	strcpy(friend[1].name,"LLLEEEEEE   DDD...KKK");
	friend[1].gender = 'F';
	friend[1].age = 23;
  friend[1].I_length = 7;
	friend[1].N_length = 7;

	strcpy(friend[2].ID,"KKKMMMUUU___CCCSSS333");
	strcpy(friend[2].name,"PPPAAARRRKKK   DDD...KKK");
	friend[2].gender = 'M';
	friend[2].age = 19;
	friend[2].I_length = 7;
	friend[2].N_length = 8;

	write();
	return 0;
}
