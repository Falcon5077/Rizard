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
unsigned char user_buff[1000], friend_buff[1000];

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

void Read_Friend(unsigned char count_fnum, info* pFRIEND);
void Write_Friend(unsigned char count_fnum, info* pFRIEND);
void WriteStr(unsigned char len, unsigned char* str);
void WriteChar(unsigned char len);
void WriteShort(unsigned short s_len);
void Write_User();
void Read_User();

// Friend List 전역 변수
unsigned char AGE_f[255]; // AGE를 문자열 202020이 아닌 숫자 ^T^T^T로 출력 atoi 사용
int count_fnum = 2;		// 동맹수 - 현재 임의 설정

// FILE
FILE *fp2;

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
		fwrite(&len, 1, sizeof(unsigned char), fp2);

}

// User Status - coin 저장 함수 ( 0 ~ 65535 )
void WriteShort(unsigned short s_len) { 

	for(int i = 0; i < 3; i++)
		fwrite(&s_len, 1, sizeof(unsigned short), fp2);

}

// User Status, Friend List 저장 함수 ( 길이만큼 더 반복 저장 )
void WriteStr(unsigned char len, unsigned char* str) {

	for(int i = 0; i < len; i++) {
		for(int j = 0; j < 3; j++)  {
			fwrite(&str[i], 1, sizeof(unsigned char), fp2);

		}
	}
}

void checkout_buff(unsigned char *buff, unsigned char *script) { //파일로 부터 받아온 Description을 확인해서 1개짜리로 바꿔 buff에 저장한다.(1차 변형)
	int len = 0, count = 0;	//len: 각 위치의 문자열 길이를 읽어서 저장시키는 변수, count: 문자열 한 줄에서 바뀌는 문자시작점~ 끝점까지의 길이 할당받는다.
	int start; //문자가 바뀌는 위치의 위치값 저장
	unsigned char strA;
	int x = 0;
	
	len = strlen(script);
	for(int k = 0; k <= len; k++) {	//len 길이만큼 반복(한줄)
		if(count == 0) {
			strA = script[k]; //반복 중 다른 문자가 시작하는 첫지점이면 그 지점의 값을 strA에 저
			start = k;
		}
		count++;
		if(strA != script[k]) {
			if(strA > 47 && strA < 58) { //입력된 값이 숫자인경우
				if(count - 1 == 1) buff[x++] = strA - 20; //같은 갯수가 1개인경우 ASCII 값에서 20빼기
				if(count - 1 == 2) buff[x++] = strA - 10; //같은 갯수가 2개인경우 ASCII값에서 10빼기
				if(count - 1 >= 3) { //반복되는 숫자가 세개 이상일 경우
					buff[x++] = strA - 10; //ASCII값 10빼고 갯수 저장
					if(count - 1 == 10) buff[x++] = 126;
					else buff[x++] = count-1;
				}
			}else {		//숫자가 아니라 문자인 경우
					if(count - 1 >= 3) { 	//같은 문자가 3개이상인 경우
							buff[x++] = strA + 32;		//아스키값 +32해서 소문자로 변경
							if(count - 1 == 10) buff[x++] = 126;
							else buff[x++] = count - 1;		//count는 현재 갯수보다 1크므로 -1해서 대입
					}
					if(count - 1 == 2) buff[x++] = strA + 32; //같은 문자가 두개인 경우 소문자 한개 저장
					if(count - 1 == 1) buff[x++] = strA; //같은 문자가 하나인 경우 그대로 저장
					}
				count = 0;
				k--;
			}
		}
	buff[x++] = '\n';
	buff[x++] = '\0';
}

void checkout_same_line(unsigned char *buff) {
	unsigned char *temp;
	unsigned char tpsave[100][100];
	unsigned char number[10];
	unsigned char *same = "=";	
	int i = 0, x = 0;

	temp = strtok(buff, "\n"); //strtok함수를 이용, \n단위로 끊어서 temp에 저장
	while(temp != NULL) { 
		if(temp !=NULL)
			strcpy(tpsave[i++], temp);
		temp = strtok(NULL, "\n");
	}

	for(int k = 0; k < i; k++) {
		for(int j = k + 1; j < i; j++) {
			if(strcmp(tpsave[k], tpsave[j]) == 0) {
				number[0] = k+1;	
				strcpy(tpsave[j], same);
				strcat(tpsave[j], number);
			}
		}
	}
	
	for(int q = 0; q < i; q++)
		printf("%s\n", tpsave[q]);

	for(int k = 0; k < i; k++) {
		for(int j = 0; j < strlen(tpsave[k]); j++) {
			for(int q = 0; q < 3; q++)
				buff[x++] = tpsave[k][j];
		}
		for(int q = 0; q < 3; q++)
			buff[x++] = '\n';
	}
	buff[x++] = '\0';	
}


void insert_file(unsigned char *buff) { //파일.... 넣을게...

	if(fp2 == NULL) {
		fprintf(stderr, "Can't Open the File!\n");
		exit(1);
	}
	fwrite(buff, sizeof(unsigned char), strlen(buff), fp2); //3번씩 저장한 최종버퍼를 encode.bin파일에 넣을게...

}

int main(int argc, char *argv[]) {
	char *fNAME;
	
	if (argc != 2) {
		printf("Error...\n");
		return 0;
	}

  fNAME = argv[1];

  FILE *fp = fopen(fNAME, "r");

  if(fp == NULL) {
		fprintf(stderr, "Error...\n");
    exit(1);
	}

  char buffer[1000];
	char *user[7];			//user 정보 저장 포인터 배열
	char *friend[4];
	char *item_save[5];
	char *des[1000];
  char *test;					
  char *tmp;
	unsigned char des_buff[1000], item_save_buff[1000];
	unsigned char last_buf[3000];

	int count_user = 0;			//user 정보 받기 위한 count 변수
	int count_item = 0;			//Item 정보 받기 위한 count 변수
	int count_friend = 0;		//동맹 정보 받기 위한 count 변수
	int line = 0;
	int index = 0;
	int x = 0, z= 0, c = 0, v = 0;
	int plz = 0;

  while(!feof(fp)) {
		test = fgets(buffer, 1000, fp);

		if(test == NULL) {
			break;
		}
		if(strstr(test, "*")) {								//필드 검사 if문
			printf("%d 번째 필드\n", ++index);
      continue;
		}
		
    switch(index) {
			case 1 : tmp = strstr(test, ":");				//tmp에 :값부터 저장							 
							 if(tmp != NULL) {							
								 if(index != 1) {
									 exit(1);
								 }
								 user[count_user] = &tmp[2];
								 if(strcmp(user[count_user],"FEMALE\n") == 0) {
									 user[count_user] = "F\n";
								 } else if(strcmp(user[count_user], "MALE\n") == 0) {
									 user[count_user] = "M\n";
								 }
								 for(int k = 0; k < strlen(user[count_user]); k++)
									 user_buff[v++] = user[count_user][k];
							 }
							 break;

 			case 2 : tmp = strstr(test, ":");
							 if(tmp != NULL) {
								 if(index != 2) {
									 exit(1);
								 }
								 item_save[count_item] = &tmp[2];
								 for(int k = 0; k < strlen(item_save[count_item]); k++)
									 item_save_buff[c++] = item_save[count_item][k];
							 }
							 break;

 		  case 3 : tmp = strstr(test, ":");
							 if(tmp != NULL) {
								 if(index != 3) {
									 exit(1);
								 }
								 friend[count_friend] = &tmp[2];
								 if(strcmp(friend[count_friend],"FEMALE\n") == 0) {
									 friend[count_friend] = "F\n";
								 } else if(strcmp(friend[count_friend], "MALE\n") == 0) {
									 friend[count_friend] = "M\n";
								 }
								 for(int k = 0; k < strlen(friend[count_friend]); k++) 
									 friend_buff[z++] = friend[count_friend][k];
								 plz++;
							 }
							 break;

			case 4 : tmp = strstr(test, "\0");
							 if(tmp != NULL) {
								 if(index != 4) {
									 exit(1);
								 }
								 des[line] = &tmp[0];
								 for(int k = 0; k < strlen(des[line]); k++)
									 des_buff[x++] = des[line][k];
								 break;
							 }
				}
	}
	user_buff[v++] = '\0'; 			//User_status
	item_save_buff[c++] = '\0'; //Item
	friend_buff[z++] = '\0';		//Friend_list
	des_buff[x++] = '\0';				//DESCRIPTION

	plz = plz / 4;
	count_fnum = plz;

	fclose(fp);

	fp2 = fopen("list.bin", "wb");

	Read_User();
	Write_User();

	info FRIEND[100];

	Read_Friend(count_fnum, FRIEND);
	Write_Friend(count_fnum, FRIEND);

	checkout_buff(last_buf, des_buff);
	checkout_same_line(last_buf);
	insert_file(last_buf);

	fclose(fp2);
	return 0;
}