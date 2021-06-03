#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* fp1;

char des[1000];

void makeSL(){
	int i=0;
	char tmp[50][50];
	char *buf;
	char number[2];
	char *same = "=";


	buf = strtok(des, "\n");
	while(buf!=NULL){
		if(buf!=NULL)
			strcpy(tmp[i++], buf);

		buf = strtok(NULL, "\n");
	}
	
	for(int k=0; k<i; k++){
		for(int u=k+1; u<i; u++){
			if(strcmp(tmp[k], tmp[u])==0){
				number[0] = k+'1';
				strcpy(tmp[u], same);
				strcat(tmp[u], number);
			}
		}
	}

	printf("%s\n", tmp[0]);
	printf("%s\n", tmp[1]);
	printf("%s\n", tmp[2]);
	printf("%s\n", tmp[3]);
	printf("%s\n", tmp[4]);
	printf("%s\n", tmp[5]);
	printf("%s\n", tmp[6]);
	printf("%s\n", tmp[7]);
}


int main(){
	fp1=fopen("decoded_data1.txt", "rt");
	int i=0;

	while(!feof(fp1)){
		fread(&des[i], sizeof(char), 1, fp1);
		i++;
	}
	
	printf("%s\n", des);
	
	makeSL();

	fclose(fp1);

	return 0;
	
}
