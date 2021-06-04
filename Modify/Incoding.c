#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* Items[] = {
   "BOMB",
   "POTION",
   "CURE",
   "BOOK",
   "SHIELD",
   "CANNON"
};

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
typedef struct {
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

// ITEM 함수
void Check_Item(void);          // 아이템을 텍스트파일에서 불러와서 하나의 문자열로 저장하는 함수
char Check_Item_sort(void);     // 그 문자열이 약속된 순서와 일치하는지 아닌지 판별하는 함수
void Write_Item(char);          // 아이템을 약속된 방식으로 파일에 쓰는 함수
void WriteChar(unsigned char);  // 파일에 쓸때 약속된 규칙으로 3회 반복해서 쓰는 함수

// ITEM 관련 변수
char* str; // 자른 문자열 저장하는 변수
char ITEM_COUNT = 0; // 아이템 총 개수 저장하는 변수
char Item_list[255] = { 0 };    // 텍스트파일을 일자로 붙인 문자열(구분은 /로 구분)
char CP_Item_list[255] = { 0 }; // Item_list의 내용이 복사된 문자열
unsigned char tmp_item_count[6] = { 0 }; // 아이템별 개수 저장하는 배열 (비어있으면 땡겨와서 저장)

// Friend List 전역 변수
unsigned char AGE_f[255]; // AGE를 문자열 202020이 아닌 숫자 ^T^T^T로 출력 atoi 사용
int count_fnum = 2;		// 동맹수 - 현재 임의 설정

// FILE
FILE* fp2;

// User Status Read 함수
void Read_User() {

	unsigned char* temp;

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
	WriteStr(idLen, id); // id 저장

	WriteChar(nameLen); // name 길이 저장
	WriteStr(nameLen, name); // name 저장

	WriteStr(genderLen, gender); // gender 저장

	WriteChar(age); // age 저장
	WriteChar(HP); // HP 저장
	WriteChar(MP); // MP 저장

	WriteShort(coin); // coin 저장

}

// Item 함수
char Check_Item_sort(void) {
	int i, num;
	char tmp_count[6] = { 0 }; // ptr과 Items[i]와 같을때의 i값
	int for_count = 0; // for문 돌아가는 횟수
	char sort = 0;

	str = strtok(Item_list, "/"); // 슬래쉬(/) 단위로 잘라서 str에 저장
	while (str != NULL) { // 자른 값이 NULL이 아닐때 
		for (i = 0; i < 6; i++) {
			if ((num = strcmp(Items[i], str)) == 0) { // str값이 Items[i] 랑 같을 때
				tmp_count[for_count++] = i;           // tmp_count에 i값 저장
				if (for_count >= 2) {                 // 비교할 값이 2개이상일때만 작동
					for (int j = 0; j < for_count - 1; j++) {
						if (tmp_count[j] > tmp_count[j + 1]) // tmp_count에 저장된 값이 순서대로가 아닐때
							return sort;  // sort 값 0으로 반환
						else
							continue;
					}
				}
				else
					break;
			}
			else if (num != 0)
				continue;
		}
		str = strtok(NULL, "/"); // 슬래쉬(/) 단위로 자르기
	}
	if (sort == 0)
		return ++sort; // 순서대로라는 뜻으로 1값 반환
}

void Write_Item(char sort) {
	int k = 0;
	unsigned char x = 0;
	int num, tmp_count = 0, result;
	unsigned binary_result = 0;
	char binary[6] = { 0 };
	if (sort == 1) {
		WriteChar(ITEM_COUNT); // 총 개수 파일에 쓰기

		if (1 <= ITEM_COUNT && ITEM_COUNT <= 4) {
			str = strtok(CP_Item_list, "/");
			while (str != NULL) {
				if (k == 6) break;
				if ((num = strcmp(Items[k++], str)) == 0) {
					binary[tmp_count++] = 1;
					str = strtok(NULL, "/");
				}

				else if (num != 0)
					binary[tmp_count++] = 0;

			}

			for (int i = 5; i >= 0; i--) {
				result = pow(2, i);
				binary_result += (unsigned char)result * binary[5 - i];
			}
			WriteChar(binary_result);
			for (int i = 0; i < ITEM_COUNT; i++)
				WriteChar(tmp_item_count[i]);
		}

		else if (ITEM_COUNT == 5) {
			str = strtok(CP_Item_list, "/");
			while (str != NULL) {
				if (k == 6) break;
				if ((num = strcmp(Items[k++], str)) == 0) {
					WriteChar(tmp_item_count[tmp_count++]);
					str = strtok(NULL, "/");
				}
				else if (num != 0) {
					WriteChar(x);
				}
			}
		}

		else if (ITEM_COUNT == 6) {
			for (int i = 0; i < 6; i++)
				WriteChar(tmp_item_count[i]);
		}
	}

	else if (sort == 0) {
		WriteChar(sort); // sort값 파일에 쓰기
		WriteChar(ITEM_COUNT);// 총 개수 파일에 쓰기

		str = strtok(CP_Item_list, "/");
		while (str != NULL) {
			for (int i = 0; i < 6; i++) {
				if ((num = strcmp(Items[i], str)) == 0) {
					WriteChar(i);
					WriteChar(tmp_item_count[tmp_count++]);
					break;
				}
				else if (num != 0)
					continue;
			}
			str = strtok(NULL, "/");
		}

	}
}

// Friend List Read 함수
void Read_Friend(unsigned char count_fnum, info* pFRIEND) {

	unsigned char* temp;
	int count = 0;

	for (int i = 0; i < count_fnum; i++) {

		if (count == 0) {	// count를 설정, friend_buff 첫 부분부터 시작, 다음 반복 실행 시 NULL부터 실행
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
void Write_Friend(unsigned char count_fnum, info* pFRIEND) {

	WriteChar(count_fnum);		// 동맹수

	for (int i = 0; i < count_fnum; i++) {		// 동맹 수 만큼 반복

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

	for (int i = 0; i < 3; i++)
		fwrite(&len, 1, sizeof(unsigned char), fp2);

}

// User Status - coin 저장 함수 ( 0 ~ 65535 )
void WriteShort(unsigned short s_len) {

	for (int i = 0; i < 3; i++)
		fwrite(&s_len, 1, sizeof(unsigned short), fp2);

}

// User Status, Friend List 저장 함수 ( 길이만큼 더 반복 저장 )
void WriteStr(unsigned char len, unsigned char* str) {

	for (int i = 0; i < len; i++) {
		for (int j = 0; j < 3; j++) {
			fwrite(&str[i], 1, sizeof(unsigned char), fp2);

		}
	}
}

void checkout_buff(unsigned char* buff, unsigned char* script) { //파일로 부터 받아온 Description을 확인해서 1개짜리로 바꿔 buff에 저장한다.(1차 변형)
	int len = 0, count = 0;	//len: 각 위치의 문자열 길이를 읽어서 저장시키는 변수, count: 문자열 한 줄에서 바뀌는 문자시작점~ 끝점까지의 길이 할당받는다.
	int start; //문자가 바뀌는 위치의 위치값 저장
	unsigned char strA;
	int x = 0;

	len = strlen(script);
	for (int k = 0; k <= len; k++) {	//len 길이만큼 반복(한줄)
		if (count == 0) {
			strA = script[k]; //반복 중 다른 문자가 시작하는 첫지점이면 그 지점의 값을 strA에 저
			start = k;
		}
		count++;
		if (strA != script[k]) {
			if (strA > 47 && strA < 58) { //입력된 값이 숫자인경우
				if (count - 1 == 1) buff[x++] = strA - 10; //같은 갯수가 1개인경우 ASCII 값에서 10빼기
				if (count - 1 == 2) buff[x++] = strA - 20; //같은 갯수가 2개인경우 ASCII값에서 20빼기
				if (count - 1 >= 3) { //반복되는 숫자가 세개 이상일 경우
					buff[x++] = strA - 10; //ASCII값 10빼고 갯수 저장
					if (count - 1 == 10) buff[x++] = 126;
					else buff[x++] = count - 1;
				}
			}
			else {		//숫자가 아니라 문자인 경우
				if (count - 1 >= 3) { 	//같은 문자가 3개이상인 경우
					buff[x++] = strA + 32;		//아스키값 +32해서 소문자로 변경
					if (count - 1 == 10) buff[x++] = 126;
					else buff[x++] = count - 1;		//count는 현재 갯수보다 1크므로 -1해서 대입
				}
				if (count - 1 == 2) buff[x++] = strA + 32; //같은 문자가 두개인 경우 소문자 한개 저장
				if (count - 1 == 1) buff[x++] = strA; //같은 문자가 하나인 경우 그대로 저장
			}
			count = 0;
			k--;
		}
	}
	buff[x++] = '\n';
	buff[x++] = '\0';
}

void checkout_same_line(unsigned char* buff) {
	unsigned char* temp;
	unsigned char tpsave[100][100];
	unsigned char number[10];
	unsigned char* same = "=";
	int i = 0, x = 0;

	temp = strtok(buff, "\n"); //strtok함수를 이용, \n단위로 끊어서 temp에 저장
	while (temp != NULL) {
		if (temp != NULL)
			strcpy(tpsave[i++], temp);
		temp = strtok(NULL, "\n");
	}

	for (int k = 0; k < i; k++) {
		for (int j = k + 1; j < i; j++) {
			if (strcmp(tpsave[k], tpsave[j]) == 0) {
				number[0] = k + 1;
				strcpy(tpsave[j], same);
				strcat(tpsave[j], number);
			}
		}
	}

	for (int k = 0; k < i; k++) {
		for (int j = 0; j < strlen(tpsave[k]); j++) {
			for (int q = 0; q < 3; q++)
				buff[x++] = tpsave[k][j];
		}
		for (int q = 0; q < 3; q++)
			buff[x++] = '\n';
	}
	buff[x++] = '\0';
}

void insert_file(unsigned char* buff) { //파일.... 넣을게...

	if (fp2 == NULL) {
		fprintf(stderr, "Can't Open the File!\n");
		exit(1);
	}
	fwrite(buff, sizeof(unsigned char), strlen(buff), fp2); //3번씩 저장한 최종버퍼를 encode.bin파일에 넣을게...

}

int main(int argc, char* argv[]) {
	char* fNAME;
	char* f2NAME;
	if (argc != 3) {
		printf("Error...\n");
		return 0;
	}

	fNAME = argv[1];
	f2NAME = argv[2];

	FILE* fp = fopen(fNAME, "r+t");

	if (fp == NULL) {
		fprintf(stderr, "Error...\n");
		exit(1);
	}

	char* ptr;  // 아이템 개수 저장하는 문자열
	char buffer[1000];
	char* user[7];			//user 정보 저장 포인터 배열
	char* friend[4];
	char* item_save[5];
	char* des[1000];
	char* test;
	char* tmp;
	unsigned char des_buff[1000], item_save_buff[1000];
	unsigned char last_buf[3000];

	int count_user = 0;			//user 정보 받기 위한 count 변수
	int count_item = 0;			//Item 정보 받기 위한 count 변수
	int count_friend = 0;		//동맹 정보 받기 위한 count 변수
	int line = 0;
	int index = 0;
	int x = 0, z = 0, c = 0, v = 0;
	int plz = 0;
	//item 변수
	char sort;
	char* line_item;
	while (!feof(fp)) {
		test = fgets(buffer, sizeof(buffer), fp);

		if (test == NULL) {
			break;
		}
		if (strstr(test, "*")) {								//필드 검사 if문
			++index;
			continue;
		}

		switch (index) {
		case 1: tmp = strstr(test, ":");				//tmp에 :값부터 저장							 
			if (tmp != NULL) {
				if (index != 1) {
					exit(1);
				}
				user[count_user] = &tmp[2];
				if (strcmp(user[count_user], "FEMALE\n") == 0) {
					user[count_user] = "F\n";
				}
				else if (strcmp(user[count_user], "MALE\n") == 0) {
					user[count_user] = "M\n";
				}
				for (int k = 0; k < strlen(user[count_user]); k++)
					user_buff[v++] = user[count_user][k];
			}
			break;

		case 2:
			do {
				if (index == 2) {
					tmp = strtok(test, " ");
					if (tmp != NULL) {
						tmp[strlen(tmp) - 1] = '\0';
						//  tmp_Items에 텍스트파일 순서로 아이템 이어 붙이기
						strcat(Item_list, tmp);
						strcat(Item_list, "/"); // /로 아이템 구분

						ptr = strtok(NULL, "\n"); // \n으로 문자열 잘라서 개수 찾기

						if (atoi(ptr) != 0) // 개수를 정수화
							tmp_item_count[ITEM_COUNT] = (unsigned char)atoi(ptr); // 정수형 배열에 대입

						else if (atoi(ptr) == 0)
							tmp_item_count[ITEM_COUNT] = 0;   //   아이템별 개수 없으면 0
					}

					if (ITEM_COUNT != 6) {
						ITEM_COUNT++; // 아이템 총 개수 계산
					}
					else
						break;
				}

				test = fgets(buffer, sizeof(buffer), fp);
				if (strlen(test) == 1)
					break;
			} while (!feof(fp));

			if (ITEM_COUNT != 6) {
				for (int i = 0; i < 6 - ITEM_COUNT; i++) { // 없는 아이템은 tmp_Items에
					strcat(Item_list, "0/");        // 0으로 저장
					tmp_item_count[ITEM_COUNT + i] = 0;    // 개수 저장 배열에도 0 대입
				}
			}
			break;

		case 3: tmp = strstr(test, ":");
			if (tmp != NULL) {
				if (index != 3) {
					exit(1);
				}
				friend[count_friend] = &tmp[2];
				if (strcmp(friend[count_friend], "FEMALE\n") == 0) {
					friend[count_friend] = "F\n";
				}
				else if (strcmp(friend[count_friend], "MALE\n") == 0) {
					friend[count_friend] = "M\n";
				}
				for (int k = 0; k < strlen(friend[count_friend]); k++)
					friend_buff[z++] = friend[count_friend][k];
				plz++;
			}
			break;

		case 4: tmp = strstr(test, "\0");
			if (tmp != NULL) {
				if (index != 4) {
					exit(1);
				}
				des[line] = &tmp[0];
				for (int k = 0; k < strlen(des[line]); k++)
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

	// Item_list을 CP_Item_list에 복사
	strcpy(CP_Item_list, Item_list);
	//저장한 값으로 아이템의 순서규칙 확인하는 함수
	//sort 값이 1이면 순서대로, 0이면 순서대로x
	sort = Check_Item_sort();
	fclose(fp);

	fp2 = fopen(f2NAME, "wb");

	Read_User();
	Write_User();

	// 약속된 규칙으로 텍스트를 인코딩하는 함수
	Write_Item(sort);

	info FRIEND[100];

	Read_Friend(count_fnum, FRIEND);
	Write_Friend(count_fnum, FRIEND);

	checkout_buff(last_buf, des_buff);
	checkout_same_line(last_buf);
	insert_file(last_buf);

	fclose(fp2);
	return 0;
}
