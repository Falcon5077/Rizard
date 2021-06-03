#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	FILE* fp;
	fp=fopen("encoded_data1.bin", "wb");
	if(fp==NULL){
		fprintf(stderr, "Error to open...\n");
		exit(1);
	}

	char* arr = "AAABBBCCCDDDEEEFFFGGGHHH";
	char enter = '\n';

	fwrite(arr, sizeof(char)*33, 1, fp);
	for(int i=0; i<3; i++)
		fwrite(&enter, sizeof(char), 1, fp);

	arr = "IIIJJJKKKLLLMMMNNNOOOPPPQQQ";
	fwrite(arr, sizeof(char)*24, 1, fp);
	for(int i=0; i<3; i++)
		fwrite(&enter, sizeof(char), 1, fp);

	arr = "RRRSSSTTTUUUVVVWWWXXXYYYZZZ";
	fwrite(arr, sizeof(char)*12, 1, fp);
	for(int i=0; i<3; i++)
		fwrite(&enter, sizeof(char), 1, fp);
	
	char one='5'-10;
	for(int i=0; i<3; i++)
		fwrite(&one, sizeof(char), 1, fp);
	char two='7'-10;
	for(int i=0; i<3; i++)
		fwrite(&two, sizeof(char), 1, fp);
	int ex=5;
	char es_c=ex;
	for(int i=0; i<3; i++)
		fwrite(&es_c, sizeof(char), 1, fp);

	char three='8'-20;
	for(int i=0; i<3; i++)
		fwrite(&three, sizeof(char), 1, fp);
	
	char ee='D';
	for(int i=0; i<3; i++)
		fwrite(&ee, sizeof(char), 1, fp);

	fclose(fp);

	return 0;
}
