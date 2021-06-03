#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// User Status 전역 변수
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

// Friend List 구조체
typedef struct{	
	unsigned char ID_len;
	unsigned char ID[255];		
 	unsigned char NAME_len;		
	unsigned char NAME[255];		
	unsigned char GENDER[255];		
	unsigned char GENDER_len; 
 	unsigned char AGE;		
}info;

// Friend List 전역 변수
unsigned char AGE_f[255]; // AGE를 문자열 202020이 아닌 숫자 ^T^T^T로 출력 atoi 사용
int count_fnum = 2;		// 동맹수 - 현재 임의 설정

// FILE
FILE *fp;

// 함수 원형 선언
void Read_Friend(unsigned char count_fnum, info* pFRIEND);
void Write_Friend(unsigned char count_fnum, info* pFRIEND);
void WriteStr(unsigned char len, unsigned char* str);
void WriteChar(unsigned char len);
void WriteShort(unsigned short s_len);
void Write_User();
void Read_User();

// 준우에게서 받을 문자열 예시
unsigned char user_buff[1000] = "KMU_CS23\nHONG CHAN PARK\nF\n20\n200\n5\n43210\n";
unsigned char friend_buff[1000] = "KMU_CS1\nHONG A\nM\n20\nKMU_CS2\nSIBAL \nF\n20\n";

// main 함수
int main(int argc,char *argv[]) {

	fp = fopen("list.bin","wb");

	Read_User(); // User Status 값 받기 
	Write_User(); // User Status 저장

// -------------------- User ------------------------

	info FRIEND[100];
	
	Read_Friend(count_fnum, FRIEND); // Friend List 값 받기
	Write_Friend(count_fnum, FRIEND); // Friend List 저장

	fclose(fp);	// 테스트 용도로 list.bin에 저장되는거 확인

// -------------------- Friend List ------------------------

	return 0;

}

// User Status Read 함수
void Read_User() {

	unsigned char *temp;

	temp = strtok(user_buff, "\n");
	strcpy(id, temp);

	temp = strtok(NULL, "\n");
	strcpy(name, temp);

	temp = strtok(NULL, "\n");
	strcpy(gender, temp);

	temp = strtok(NULL, "\n"); // atoi로 문자 배열에서 int형 숫자로 변환
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


// User Status Write 함수
void Write_User() {

	idLen = strlen(id);
	nameLen = strlen(name);
	genderLen = strlen(gender);

	WriteChar(idLen); // id 길이 저장
	WriteStr(idLen,id); // id 저장

	WriteChar(nameLen); // name 길이 저장
	WriteStr(nameLen,name); // name 저장

	WriteStr(genderLen, gender); // gender 저장

	WriteChar(age); // age 저장
	WriteChar(HP); // HP 저장
	WriteChar(MP); // MP 저장

	WriteShort(coin); // coin 저장

}


// Friend List Read 함수
void Read_Friend(unsigned char count_fnum, info* pFRIEND){

	unsigned char *temp;
	int count = 0;

	for (int i = 0; i < count_fnum; i++){
	
		if (count == 0){	// count를 설정, friend_buff 첫 부분부터 시작, 다음 반복 실행 시 NULL부터 실행
			temp = strtok(friend_buff, "\n"); 
			strcpy(pFRIEND->ID, temp);
			count++;
		}
		else {
			temp = strtok(NULL, "\n");
	  	strcpy(pFRIEND->ID, temp); 
		}

		temp = strtok(NULL, "\n"); 
		strcpy(pFRIEND->NAME, temp);		
		
	 	pFRIEND->ID_len = strlen(pFRIEND->ID);		
		pFRIEND->NAME_len = strlen(pFRIEND->NAME);
 		
		temp = strtok(NULL, "\n");
		strcpy(pFRIEND->GENDER, temp);
		
		temp = strtok(NULL, "\n");
		strcpy(AGE_f, temp);

	 	pFRIEND->AGE = atoi(AGE_f); // atoi로 문자 배열에서 int형 숫자로 변환
		
		pFRIEND->GENDER_len = strlen(pFRIEND->GENDER); 
	  
		pFRIEND++;	// 구조체 배열 1 증가. ex) FRIEND[0] 에서 [1]로
	}	
}

// Friend List Write 함수
void Write_Friend(unsigned char count_fnum, info *pFRIEND){

	WriteChar(count_fnum);		// 동맹수

	for (int i = 0; i < count_fnum; i++)	{		// 동맹 수 만큼 반복
			
		WriteChar(pFRIEND->ID_len);		// 아이디 길이
		WriteStr(pFRIEND->ID_len, pFRIEND->ID);		// 아이디

		WriteChar(pFRIEND->NAME_len);		// 이름 길이
		WriteStr(pFRIEND->NAME_len, pFRIEND->NAME);		// 이름

		WriteStr(pFRIEND->GENDER_len, pFRIEND->GENDER);		// 성별
		WriteChar(pFRIEND->AGE);		// 나이
		
		pFRIEND++;		
	}
}

// User Status, Friend List 저장 함수 ( 반복 저장 )
void WriteChar(unsigned char len) {

	for(int i = 0; i < 3; i++)
		fwrite(&len, 1, sizeof(unsigned char), fp);

}

// User Status - coin 저장 함수 ( 0 ~ 65535 )
void WriteShort(unsigned short s_len) { 

	for(int i = 0; i < 3; i++)
		fwrite(&s_len, 1, sizeof(unsigned short), fp);

}

// User Status, Friend List 저장 함수 ( 길이만큼 더 반복 저장 )
void WriteStr(unsigned char len, unsigned char* str) {

	for(int i = 0; i < len; i++) {
		for(int j = 0; j < 3; j++)  {
			fwrite(&str[i], 1, sizeof(unsigned char), fp);

		}
	}
}
