#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{	
	unsigned char ID_len; 		// ID 길이
	char ID[255]; 						// ID
 	unsigned char NAME_len;		// name 길이
	char NAME[255]; 					// name	
	char GENDER; 							// gender 첫글자만 받아온다 M or F
 	char AGE; 								// age	
}info;

char NUM; // 동맹수 1 부터 시작해야함. FRIEND 1 ID . . .  

FILE *fp;

void Read_data(info* pFRIEND);
void Write_data(info* pFRIEND);
void WriteStr(unsigned char len, char* str);
void WriteChar(unsigned char len);


// 받아오는건 대충 일캐?
void Read_data(info* pFRIEND){
	
	for (int i = 0; i < NUM; i++){

		fread(&pFRIEND, sizeof(pFRIEND), 1, fp);	
		pFRIEND++;

	}	

}

void Write_data(info *pFRIEND){

	for (int i = 0; i < NUM; i++)	{ // 동맹 수 만큼 반복
		
		pFRIEND->ID_len = strlen(pFRIEND->ID); 			// 아이디 길이 구하기
		pFRIEND->NAME_len = strlen(pFRIEND->NAME); 	// 이름 길이 구하기
  	
		WriteChar(NUM); // 동맹수
		
		WriteChar(pFRIEND->ID_len); 						// 아이디 길이
		WriteStr(pFRIEND->ID_len, pFRIEND->ID);	// 아이디

		WriteChar(pFRIEND->NAME_len); 							// 이름 길이
		WriteStr(pFRIEND->NAME_len, pFRIEND->NAME);	// 이름

		WriteChar(pFRIEND->GENDER);	// 성별
		WriteChar(pFRIEND->AGE);		// 나이

		pFRIEND++; // 구조체 배열 1 증가. ex) FRIEND[0] 에서 [1]로
	}
}

void WriteStr(unsigned char len, char* str) {

	for(int i = 0; i < len; i++) {

		for(int j = 0; j < 3; j++) {

			fwrite(&str[i], 1, sizeof(unsigned char), fp);

		}
	}
}

void WriteChar(unsigned char len) {

	for(int i = 0; i < 3; i++) {

		fwrite(&len, 1, sizeof(unsigned char), fp);

	}
}

int main(int argv, char *argc[]) {

	fp = fopen("list.bin", "wb");

	info FRIEND[100]; // 구조체 배열 FRIEND로 선언 최대 100명까지

  Read_data(FRIEND);
	Write_data(FRIEND);
	
	fclose(fp);
	return 0;
}
