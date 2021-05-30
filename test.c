#include <stdio.h>
#include <string.h>
int main() {
	FILE *fp = fopen("project.bin","wb");
	char ID[255] = {0,};
	char name[255]= {0,};
	char age = 22;
	char gender = 'M';

	strcpy(ID,"KMU_CS1");
	strcpy(name,"KIM S");

	for(int i =0; ID[i] != 0; i++) {
		for(int j = 0; j < 3; j++) {
			fwrite(&ID[i],sizeof(char),1,fp);
		}
	}

	for(int i = 0; name[i] != 0; i++) {
		for(int j = 0; j<3; j++) {
			fwrite(&name[i],sizeof(char),1,fp);
		}
	}

	for(int i = 0; i<3; i++) {
		fwrite(&gender,sizeof(char),1,fp);
	}

	for(int i = 0; i < 3; i++) {
		fwrite(&age,sizeof(char),1,fp);
	}

	return 0;
}
