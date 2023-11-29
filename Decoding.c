#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 함수 선정의
void Write_USER_STATUS(void);
void Write_ITEMS(void);

void Checkstr_I(char* buffer, int F_num);
void Checkstr_N(char* buffer, int F_num);

void FRIEND_READ();
void FRIEND_SAVE();
void fprint();

unsigned char CheckUnchar(unsigned char* tmp);
unsigned char ReadUnchar();
void makedes();
void ArrToTxt();

unsigned short CheckShort(unsigned short* tmp);
unsigned short ReadShort();
void ReadStr(char len, char* target); // char를 len 길이만큼 읽는 함수
#define MAX 255

FILE* fp1;
FILE* fp2;

char* modified;
char* final_result;

// main 함수
int main(int argc, char* argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Error Argument...\n");
		fprintf(stderr, "Input Example : ./Decoding.out Incoding_output.txt Decoding_output.txt \n");
		return 0;
	}

	modified = argv[1];
	final_result = argv[2];
	fp1 = fopen(modified, "rb");
	fp2 = fopen(final_result, "w+t");

	// 유저 정보 출력
	Write_USER_STATUS();

	Write_ITEMS();

	// FRIEND
	FRIEND_READ();
	FRIEND_SAVE();
	fprint();

	//
	makedes();
	ArrToTxt();

	fclose(fp1);
	fclose(fp2);

	return 0;
}

// 유저
void Write_USER_STATUS(void) {
	unsigned char tmpLen;		//문자열 길이를 받아올 변수
	fprintf(fp2, "*USER STATUS*\n");

	tmpLen = ReadUnchar();		// ID의 길이를 읽음
	ReadStr(tmpLen, "ID");		// ID길이만큼 ID 읽음

	tmpLen = ReadUnchar();		// 이름의 길이를 읽음
	ReadStr(tmpLen, "NAME");		// 이름의 길이만큼 이름을 읽음

	tmpLen = ReadUnchar();		// 성별을 읽고 출력함
	if (tmpLen == 'M')		// 읽은 char 값이 M이면 MALE
		fprintf(fp2, "GENDER: MALE\n");
	else if (tmpLen == 'F')	// F면 FEMALE 출력
		fprintf(fp2, "GENDER: FEMALE\n");

	tmpLen = ReadUnchar();		// 나이를 읽고 출력함
	fprintf(fp2, "AGE: %d\n", tmpLen);

	tmpLen = ReadUnchar();		// HP를 읽고 출력함
	fprintf(fp2, "HP: %d\n", tmpLen);

	tmpLen = ReadUnchar();		// MP를 읽고 출력함
	fprintf(fp2, "MP: %d\n", tmpLen);

	unsigned short tmp = ReadShort();	// unsigned short 타입
	fprintf(fp2, "COIN: %d\n", tmp);	// Coin을 읽고 출력함

	fprintf(fp2, "\n");
}

// 아이템 변수
// 앞에서부터 아이템 순서를 인지하는 변수, 아이템 총 개수, 아이템별 개수 저장하는 변수
unsigned char ITEMS_sort, ITEMS_count, ITEMS_num;

// 순서대로 ITEM_NAME[0] ~ ITEM_NAME[5]
char* ITEM_NAME[] = {
   "BOMB",
   "POTION",
   "CURE",
   "BOOK",
   "SHIELD",
   "CANNON"
};

// 아이템 디코딩 함수
void Write_ITEMS(void) {
	ITEMS_sort = ReadUnchar(); // 파일에 있는 순서를 ITEM_sort 변수에 불러오고, 
	fprintf(fp2, "*ITEMS*\n");

	// ITEM_sort 값이 0이면 본래의 텍스트가 ITEM_NAME[]의 문자열 순서대로 정렬되지 않음을 의미
	if (ITEMS_sort == 0) {
		ITEMS_count = ReadUnchar(); // 파일에 있는 아이템 개수를 ITEMS_count에 저장
		unsigned char ITEMS[ITEMS_count * 2];    // 배열의 크기를 ITEMS_count * 2로 선언
		for (int i = 0; i < ITEMS_count * 2; i++)
			ITEMS[i] = ReadUnchar(); // ITEMS[]에 차례대로 아이템 종류와 개수를 입력

		for (int j = 0; j < ITEMS_count * 2; j++) {
			fprintf(fp2, "%s: ", ITEM_NAME[ITEMS[j]]);
			fprintf(fp2, "%d\n", ITEMS[++j]);
		}
	}

	// ITEM_sort 값이 0이 아니면 본래의 텍스트가 ITEM_NAME[]의 문자열 순서대로 정렬됐음을 의미
	else if (ITEMS_sort != 0) {
		ITEMS_count = ITEMS_sort; // ITEMS_sort가 0이 아닌 경우 바로 총 개수로 인지하고 ITEMS_count에 대입
		if ((ITEMS_count >= 1) && (ITEMS_count <= 4)) { // ITEMS 갯수가 1이상 4이하일때
			char ITEMS[6]; // 10진수 값을 소인수분해해서 ITEMS배열에 저장
			int T_num = ReadUnchar(), n = 6; // 파일에서 10진수 값을 받아와서
			while (n != 0) {
				ITEMS[--n] = T_num % 2; // 10진수 값을 2진수 형태로 소인수 분해
				T_num /= 2;
			}
			for (int i = 0; i < 6; i++) {
				if (ITEMS[i] != 0) { // 2진수 값이 1일 경우
					ITEMS_num = ReadUnchar(); // ITEMS_num를 읽어와서
					fprintf(fp2, "%s: %d\n", ITEM_NAME[i], ITEMS_num); // 아이템 이름과 개수를 출력
				}
				else
					continue; // 2진수 값이 1이 아닐경우, 즉 0일경우 출력하지 않고 건너뜀
			}
		}
		else if (ITEMS_count == 5) { // ITEMS 갯수가 5일때
			unsigned char ITEMS[6];   // 배열의 크기는 6으로 고정
			for (int i = 0; i < 6; i++) { // 저장된 형태는 배열 6개에 아이템별 개수만 저장되어 있으므로
				ITEMS[i] = ReadUnchar();   // 차례대로 압축규칙 해소
				if (ITEMS[i] == '*') // ITEMS배열에 저장된 수가 0이면 출력 x
					continue;
				fprintf(fp2, "%s: %d\n", ITEM_NAME[i], ITEMS[i]); // 0이 아니면 출력
			}
		}

		else if (ITEMS_count == 6) {
			unsigned char ITEMS[6];   // 배열의 크기는 6으로 고정
			for (int i = 0; i < 6; i++) { // 저장된 형태는 배열 6개에 아이템별 개수만 저장되어 있으므로
				ITEMS[i] = ReadUnchar();   // 차례대로 압축규칙 해소
				fprintf(fp2, "%s: %d\n", ITEM_NAME[i], ITEMS[i]); // 0이 아니면 출력
			}
		}
	}
	fprintf(fp2, "\n"); // 줄바꿈 출력
}


// 동맹 변수
typedef struct {
	unsigned char I_length; // ID길이
	unsigned char N_length; // 이름 길이
	char ID[255]; //ID
	char name[255]; //이름
	char gender; // 성별
	char age; // 나이
	char buffer[1000]; // ID 버퍼
	char buffer_n[1000]; // 이름 버퍼
	char buffer_g[3]; // 성별 버퍼
	char buffer_age[3]; // 나이 버퍼
}info; // 동맹 구조체

info FRIEND[100]; //동맹 배열
unsigned char num; // 동맹수

void Checkstr_I(char* buffer, int F_num) { // ID buffer에 저장된 데이터에서 필요한 정보를 추출해 ID정보를 받아오는 함수
	char tmp[3]; // 3개의 저장된 정보를 받아오는 배열
	int index = 0;
	for (int i = 0; buffer[i] != 0; i = i + 3) {
		tmp[0] = buffer[i];
		tmp[1] = buffer[i + 1];
		tmp[2] = buffer[i + 2]; //tmp 안에 저장된 buffer정보를 받은후
		FRIEND[F_num].ID[index] = CheckUnchar(tmp); // Checkunchar 로 3개중 검증된 하나의 정보를 추출한다.
		index++;
		//이 과정을 buffer배열이 끝날때까지 반복해 한글자씩 ID구조체 변수에 받아온다.
	}
}

void Checkstr_N(char* buffer, int F_num) { //Name buffer에 저장된 데이터에서 필요한 정보를 추출해 name정보를 받아오는 함수 
	char tmp[3]; // 3개의 저장된 정보를 받아오는 배열
	int index = 0;
	for (int i = 0; buffer[i] != 0; i = i + 3) {
		tmp[0] = buffer[i];
		tmp[1] = buffer[i + 1];
		tmp[2] = buffer[i + 2]; // tmp 안에 저장된 buffer 정보를 받은후
		FRIEND[F_num].name[index] = CheckUnchar(tmp); // Checkunchar 로 3개중 검증된 하나의 정보를 추출한다.
		index++;
	}
	//이 과정을 buffer 배열이 끝날때 까지 반복해 한글자씩 name구조체 변수에 받아온다.
}

void FRIEND_READ() {
	// 인코더 파일에서 각각의 정보들을 해당하는 buffer에 저장한다. but, 동맹수 ID길이 이름길이의 경우에는 ReadUnchar를 이용해 바로 필요한 정보를 읽어내어 저장한다. 
	num = ReadUnchar(); // 동맹수를 읽어 저장한다.
	for (int i = 0; i < num; i++) {
		FRIEND[i].I_length = ReadUnchar(); // ID길이 저장
		fread(FRIEND[i].buffer, sizeof(char), FRIEND[i].I_length * 3, fp1); // ID buffer에 정보입력
		FRIEND[i].N_length = ReadUnchar(); // name길이 
		fread(FRIEND[i].buffer_n, sizeof(char), FRIEND[i].N_length * 3, fp1); //name buffer에 정보입력
		fread(FRIEND[i].buffer_g, sizeof(char), 3, fp1); // 성별 buffer에 정보입력
		fread(FRIEND[i].buffer_age, sizeof(char), 3, fp1); // 나이 buffer에 정보입력
	}
}
void FRIEND_SAVE() { // buffer에 있는 정보를 걸러서 해당하는 구조체변수에 저장
	for (int i = 0; i < num; i++) {
		Checkstr_I(FRIEND[i].buffer, i);
		Checkstr_N(FRIEND[i].buffer_n, i);
		FRIEND[i].gender = CheckUnchar(FRIEND[i].buffer_g);
		FRIEND[i].age = CheckUnchar(FRIEND[i].buffer_age);
	}
}

void fprint() { // 구조체변수안에 있는 데이터를 형식에 맞춰서 fprintf로 텍스트파일에 입력해준다.
	fprintf(fp2, "*FRIENDS LIST*\n");
	for (int i = 0; i < num; i++) {
		fprintf(fp2, "FRIEND%d ID: %s\n", i + 1, FRIEND[i].ID);
		fprintf(fp2, "FRIEND%d NAME: %s\n", i + 1, FRIEND[i].name);
		if (FRIEND[i].gender == 'M') {
			fprintf(fp2, "FRIEND%d GENDER: MALE\n", i + 1);
		}
		else {
			fprintf(fp2, "FRIEND%d GENDER: FEMALE\n", i + 1);
		}
		fprintf(fp2, "FRIEND%d AGE: %d\n\n", i + 1, FRIEND[i].age);
	}
}

// Description
#define DES_MAX_SIZE 1000 //description은 1000byte까지 작성할수있다.

unsigned char des[DES_MAX_SIZE]; //변형된 description저장할 변수
unsigned char txt[DES_MAX_SIZE]; //해석한 description저장할 변수

unsigned char CheckUnchar(unsigned char* tmp) { //unchar3개 중 한개출력
	unsigned char real;

	if (tmp[0] != tmp[1]) {
		if (tmp[0] != tmp[2]) {
			if (tmp[1] == tmp[2]) {
				real = tmp[1];
			}
			else {
				real = tmp[1];
			}
		}
		else {
			real = tmp[2];
		}
	}
	else {
		real = tmp[0];
	}

	return real;
}


// 디스크립션
unsigned char ReadUnchar() { //unchar 3개 읽기
	unsigned char len[3];
	unsigned char m_unchar;

	for (int i = 0; i < 3; i++) {
		fread(&len[i], sizeof(unsigned char), 1, fp1);
	}
	m_unchar = CheckUnchar(len);

	return m_unchar;
}

void makedes() { // 파일 가져오기
	int i = 0;
	while (!feof(fp1)) {
		des[i++] = ReadUnchar();
	}

	des[i - 1] = '\0';
}

void ArrToTxt() { //파일 해석하기
	int i = 0; //des배열 반복위한 변수
	int u = 0; //txt배열 반복위한 변수

	int n = 0; //반복횟수 저장변수
	int d = 0; //반복문장 가져올 시 처음부터 검사할 변수

	fprintf(fp2, "*DESCRIPTION*\n");
	while (des[i]) { //배열 끝까지 반복		
		if (des[i] >= 'A' && des[i] <= 'Z') { //문자가 반복되지않고 나올때
			txt[u] = des[i++];
			fprintf(fp2, "%c", txt[u++]);
		}
		else if (des[i] == '\n') { //개행문자가 나올때
			txt[u] = des[i++];
			fprintf(fp2, "%c", txt[u++]);
		}
		else if (des[i] >= '0' - 10 && des[i] <= '9' - 10) { //한자리 또는 세자리 이상숫자일때
			if (des[i + 1] >= 3 && des[i + 1] <= 28 && des[i + 1] != 10) { //세자리 이상 숫자일때
				n = des[i + 1];
				for (int k = 0; k < n; k++) { //다음칸에 나오는 반복숫자만큼 반복
					txt[u] = des[i] + 10;
					fprintf(fp2, "%c", txt[u++]);
				}
				i = i + 2;
			}
			else if (des[i + 1] == 126) { //10번 반복될때
				n = 10;
				for (int k = 0; k < n; k++) {
					txt[u] = des[i] + 10;
					fprintf(fp2, "%c", txt[u++]);
				}
				i = i + 2;
			}
			else { //한자리 숫자일때
				txt[u] = des[i++] + 10;
				fprintf(fp2, "%c", txt[u++]);
			}
		}
		else if (des[i] >= '0' - 20 && des[i] <= '9' - 20) { //두자리 숫자일때
			txt[u++] = des[i] + 20;
			txt[u++] = des[i] + 20;
			fprintf(fp2, "%c%c", txt[u - 2], txt[u - 1]);
			i++;
		}
		else if (des[i] >= 'a' && des[i] <= 'z') { //반복되는 문자의 경우
			if (des[i + 1] >= 3 && des[i + 1] <= 28 && des[i + 1] != 10) { //세번이상 반복되는 문자
				n = des[i + 1];
				for (int k = 0; k < n; k++) {
					txt[u] = des[i] - 32;
					fprintf(fp2, "%c", txt[u++]);
				}
				i = i + 2;
			}
			else if (des[i + 1] == 126) { //10번 반복될때
				n = 10;
				for (int k = 0; k < n; k++) {
					txt[u] = des[i] - 32;
					fprintf(fp2, "%c", txt[u++]);
				}
				i = i + 2;
			}
			else { //두번 반복되는 경우
				txt[u++] = des[i] - 32;
				txt[u++] = des[i] - 32;
				fprintf(fp2, "%c%c", txt[u - 2], txt[u - 1]);
				i++;
			}
		}
		else if (des[i] == '=') { //문장반복구문 나올경우
			d = 0;
			n = des[i + 1];
			if (n == 126)
				n = 10;

			while (n != 1) {
				if (txt[d] == '\n') {
					n = n - 1;
				}
				d++;
			}

			while (txt[d] != '\n') {
				txt[u] = txt[d++];
				fprintf(fp2, "%c", txt[u++]);
			}

			i = i + 2;
		}
		else {
			fprintf(fp2, "%c", des[i]);
			i++;
		}
	}
}

unsigned short CheckShort(unsigned short* tmp)		// tmp 가 KKK 이면
{
	unsigned short real;

	if (tmp[0] != tmp[1])	// tmp[0] K랑 tmp[1] K가 같은지 비교
	{
		if (tmp[0] != tmp[2])	// 0이랑 1이 틀다면 0이랑 2가 같은지 비교
		{
			if (tmp[1] == tmp[2])	// 같다면 1이랑 2, 2개가 같기때문에
			{
				real = tmp[1];	// real에 tmp중 1이나 2 아무거나 넣어서 리턴	(XKK) 의 경우
			}
			else
			{
				//printf("셋다 틀림 ");
				real = tmp[1];
			}
		}
		else	// 0이랑 2가 같다면 real에 0을 넣어서 리턴 (KXK) 의 경우
		{
			real = tmp[0];
		}
	}
	else
	{
		real = tmp[0];	// 0이랑 1이 같으니 (KKX)의 경우
	}

	return real;
}

unsigned short ReadShort() {
	unsigned short len[3];
	unsigned short m_short;

	for (int t = 0; t < 3; t++)
		fread(&len[t], sizeof(unsigned short), 1, fp1);

	m_short = CheckShort(&len[0]);

	return m_short;
}

void ReadStr(char len, char* target) {	// 읽을 문자열 길이 len과 필드명 target
	unsigned char str[255] = " ";

	for (int p = 0; p < len; p++) {		// 문자열 길이 만큼 반복
		char temp[3];

		for (int k = 0; k < 3; k++)
			fread(&temp[k], sizeof(unsigned char), 1, fp1);

		char a = CheckUnchar(&temp[0]);	// 읽어온 char 3개를 Check 함수로 보내서 복원시킴
		str[p] = a;	// 복원 시킨 값을 str[p]에 저장해서 문자열을 완성
	}
	fprintf(fp2, "%s: %s\n", target, str);
}
