#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{	
	unsigned char ID_len;		// ID 길이
	unsigned char ID[255];		// ID
 	unsigned char NAME_len;		// name 길이
	unsigned char NAME[255];		// name	
	unsigned char GENDER[255];		// gender 첫글자만 받아온다 M or F
	unsigned char GENDER_len; // 성별 길이
 	unsigned char AGE;		// age
}info;

unsigned char AGE_f[255]; // AGE를 문자열 202020이 아닌 숫자 ^T^T^T로 출력
int count_fnum = 5;		// 동맹수 1 부터 시작해야함. FRIEND 1 ID . . .   

FILE *fp;

void Read_data(unsigned char count_fnum, info* pFRIEND);
void Write_data(unsigned char count_fnum, info* pFRIEND);
void WriteStr(unsigned char len, char* str);
void WriteChar(unsigned char len);

// main 함수
int main(int argv, char *argc[]) {

	fp = fopen("list.bin", "wb");

	info FRIEND[100];		// 구조체 배열 FRIEND로 선언 최대 100명까지

  Read_data(count_fnum, FRIEND);
	Write_data(count_fnum, FRIEND);
	
	fclose(fp);
	return 0;
}

// Read 함수
void Read_data(unsigned char count_fnum, info* pFRIEND){

	unsigned char friend_buff[1000] = "KMU_CS1\nHONG A\nM\n20\nKMU_CS2\nSIBAL \nF\n30\n";
	unsigned char *temp;
	int count = 0;

	for (int i = 0; i < count_fnum; i++){
	
		if (count == 0){
			temp = strtok(friend_buff, "\n"); // KMU_CS1 까지 짜른다. 템프에 저장, 
			strcpy(pFRIEND->ID, temp); // KMU_CS1을 pFRIEND->ID에 저장
			count++;
		}
		else {
			temp = strtok(NULL, "\n"); // KMU_CS1 까지 짜른다. 템프에 저장, 
	  	strcpy(pFRIEND->ID, temp); // KMU_CS1을 pFRIEND->ID에 저장
		}

		temp = strtok(NULL, "\n"); // strtok 포인터가 이동을 안함... 
		strcpy(pFRIEND->NAME, temp);		
		
	 	pFRIEND->ID_len = strlen(pFRIEND->ID);		// 아이디 길이 구하기
		pFRIEND->NAME_len = strlen(pFRIEND->NAME);		// 이름 길이 구하기
 		
		temp = strtok(NULL, "\n");
		strcpy(pFRIEND->GENDER, temp);
		
		temp = strtok(NULL, "\n");
		strcpy(AGE_f, temp);

	 	pFRIEND->AGE = atoi(AGE_f);
		
		pFRIEND->GENDER_len = strlen(pFRIEND->GENDER);
	  
		pFRIEND++;
	}	
}

// Write 함수
void Write_data(unsigned char count_fnum, info *pFRIEND){

	WriteChar(count_fnum);		// 동맹수

	for (int i = 0; i < count_fnum; i++)	{		// 동맹 수 만큼 반복
			
		WriteChar(pFRIEND->ID_len);		// 아이디 길이
		WriteStr(pFRIEND->ID_len, pFRIEND->ID);		// 아이디

		WriteChar(pFRIEND->NAME_len);		// 이름 길이
		WriteStr(pFRIEND->NAME_len, pFRIEND->NAME);		// 이름

		WriteStr(pFRIEND->GENDER_len, pFRIEND->GENDER);		// 성별
		WriteChar(pFRIEND->AGE);		// 나이
		
		pFRIEND++;		// 구조체 배열 1 증가. ex) FRIEND[0] 에서 [1]로
	}
}

// 문장입력
void WriteStr(unsigned char len, char* str) {

	for(int i = 0; i < len; i++) {

		for(int j = 0; j < 3; j++) {

			fwrite(&str[i], 1, sizeof(unsigned char), fp);
	
		}
	}
}

// 단어입력
void WriteChar(unsigned char len) {

	for(int i = 0; i < 3; i++) {

		fwrite(&len, 1, sizeof(unsigned char), fp);

	}
}


/* count_fnum(동맹수) 값을 받아서 반복함.
	 현재 segmentation 뜨는데 이건 배열의 길이가 동맹수보다 작아서 뜨는 오류임
	 배열의 길이를 받아서 동맹 수 만큼 할당받으면 걱정 없음 */
