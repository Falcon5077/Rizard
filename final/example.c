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

	unsigned char* arr = "THIS IS EXAMPLE";
	char tmp = 0;
	char IDlen = 9;
	for(int i=0; i<3; i++)
		fwrite(&IDlen, sizeof(char), 1, fp);
	
	//MAKE USER STATUS
	arr = "KKKMMMUUU___CCCSSS111222333";
	fwrite(arr, 27, 1, fp);
	
	char Namelen = 4;
	for(int i=0; i<3; i++)
		fwrite(&Namelen, sizeof(char), 1, fp);

	arr = "HHHOOONNNGGG";
	fwrite(arr, 12, 1, fp);

	arr = "FFF";
	fwrite(arr, 3, 1, fp);

	char age = 33;
	for(int i=0; i<3; i++)
		fwrite(&age, sizeof(char), 1, fp);

	char HP = 200;
	for(int i=0; i<3; i++)
		fwrite(&HP, sizeof(char), 1, fp);

	char MP = 5;
	for(int i=0; i<3; i++)
		fwrite(&MP, sizeof(char), 1, fp);

	unsigned short Coin = 43210;
	for(int i=0; i<3; i++)
		fwrite(&Coin, sizeof(unsigned short), 1, fp);

	//MAKE ITEM LIST
	tmp = 3;
	for(int i=0; i<3; i++)
		fwrite(&tmp, sizeof(char), 1, fp);

	tmp = 56;
	for(int i=0; i<3; i++)
		fwrite(&tmp, sizeof(char), 1 ,fp);

	tmp = 1;
	for(int i=0; i<3; i++)
		fwrite(&tmp, sizeof(char), 1, fp);

	tmp = 3;
	for(int i=0; i<3; i++)
		fwrite(&tmp, sizeof(char), 1, fp);

	tmp = 10;
	for(int i=0; i<3; i++)
		fwrite(&tmp, sizeof(char), 1, fp);

	//FRIEND LIST
	tmp = 2; //FRIEND MEMBER
	for(int i=0; i<3; i++)
		fwrite(&tmp, sizeof(char), 1, fp);

	IDlen = 7;
	Namelen = 5;

	for(int i=0; i<3; i++)
		fwrite(&IDlen, sizeof(char), 1, fp);

	arr="KKKMMMUUU___CCCSSS111";
	fwrite(arr, 21, 1, fp);

	for(int i=0; i<3; i++)
		fwrite(&Namelen, sizeof(char), 1, fp);
	
	arr = "KKKIIIMMM   SSS";
	fwrite(arr, 15, 1, fp);
	
	arr = "MMM";
	fwrite(arr, 3, 1, fp);
	
	char age_f = 12;

	for(int i=0; i<3; i++)
		fwrite(&age_f, sizeof(char), 1, fp);

	for(int i=0; i<3; i++)
		fwrite(&IDlen, sizeof(char), 1, fp);
	
	arr="KKKMMMUUU___CCCSSS222";
	fwrite(arr, 21, 1, fp);

	for(int i=0; i<3; i++)
		fwrite(&Namelen, sizeof(char), 1, fp);

	arr = "LLLEEEEEE   DDD";
	fwrite(arr, 15, 1, fp);

	arr = "FFF";
	fwrite(arr, 3, 1, fp);

	age_f = 30;

	for(int i=0; i<3; i++)
		fwrite(&age_f, sizeof(char), 1, fp);


	//MAKE DESCRIPTION
	char enter = '\n';
	char buf;
	arr = "AAABBBaaadddeeeGGGAAAggg";
	fwrite(arr, 24, 1, fp);

	buf = '1'-20;
	for(int i=0; i<3; i++)
		fwrite(&buf, 1, 1, fp);

	for(int i=0; i<3; i++)
		fwrite(&enter, 1, 1, fp);

	arr="AAA";
	fwrite(arr, 3, 1, fp);

	buf = 4;
	for(int i=0; i<3; i++)
		fwrite(&buf, 1, 1, fp);

	arr="bbbCCCbbbCCCbbbCCC";
	fwrite(arr, 18, 1, fp);

	for(int i=0; i<3; i++)
		fwrite(&enter, 1, 1, fp);

	arr = "HHHEEElllOOO";
	fwrite(arr, 15, 1, fp);

	for(int i=0; i<3; i++)
		fwrite(&enter, 1, 1, fp);

	arr = "aaa";
	fwrite(arr, 3, 1, fp);

	buf = 5;
	for(int i=0; i<3; i++)
		fwrite(&buf, 1, 1, fp);

	arr = "CDEkkkhhhlll";
	fwrite(arr, 12, 1, fp);

	for(int i=0; i<3; i++)
		fwrite(&enter, 1, 1, fp);

	buf = '=';
	for(int i=0; i<3; i++)
		fwrite(&buf, 1, 1, fp);

	buf = 2;
	for(int i=0; i<3; i++)
		fwrite(&buf, 1, 1, fp);

	fclose(fp);

	return 0;
}
