#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 255
char* modified;
char* final_result;

FILE* fp1;
FILE* fp2;
// 규칙해소 함수들
char CheckChar(char* len);
unsigned short CheckShort(unsigned short* tmp);
char ReadLen(void);
unsigned short ReadShort();
void ReadStr(char len, char* target);
// 텍스트 출력 함수
void Write_USER_STATUS(void);
void Write_ITEMS(void);

// 기은 
typedef struct {
	unsigned char I_length;
	unsigned char N_length;
	char ID[255];
	char name[255];
	char gender;
	char age;
	char buffer [1000];
	char buffer_n[1000];
	char buffer_g[3];
	char buffer_age[3];
}info; // 동맹 구조체

info FRIEND[100]; //동맹 배열

unsigned char num; // 동맹수

char checkChar(char *tmp)
{
	char real;

	if(tmp[0] != tmp[1])
	{
		if(tmp[0] != tmp[2])
		{
			if(tmp[1] == tmp[2])
			{
				real = tmp[1];
			}
			else
			{
				//printf("셋다 틀림 ");
				real = tmp[1];
			}
		}
		else
		{
			real = tmp[0];
		}
	}
	else
	{
		real = tmp[0];
	}
	return real;
}


void Checkstr_I(char *buffer,int F_num) {
	char tmp[3];
	int index = 0;
	for(int i = 0; buffer[i] !=0; i = i + 3) {
			tmp[0] = buffer[i];
			tmp[1] = buffer[i+1];
			tmp[2] = buffer[i+2];
			FRIEND[F_num].ID[index]= checkChar(tmp);
			index++;
	}
} //ID buffer에 저장된 데이터를 추출한다.

void Checkstr_N(char *buffer,int F_num) {
	char tmp[3];
	int index = 0;
	for(int i =0; buffer[i] !=0; i = i+3) {
		tmp[0] = buffer[i];
		tmp[1] = buffer[i+1];
		tmp[2] = buffer[i+2];
		FRIEND[F_num].name[index] = checkChar(tmp);
		index++;
	}
} //name buffer에 저장된 데이터를 추출한다.

void print() {
	printf("*FRIENDS LIST*\n");
	for(int i = 0; i< num; i++) {
		printf("ID : %s\n",FRIEND[i].ID);
		printf("NAME : %s\n",FRIEND[i].name);
		if(FRIEND[i].gender=='M') {
			printf("GENDER : MALE\n");
		}
		else {
			printf("GENDER : FEMALE\n");
		}
		printf("AGE : %d\n\n",FRIEND[i].age);
	}
}

void FRIEND_READ() { // 인코더 파일 읽어오는 함수
	num = ReadLen(); // 동맹수를 읽어 온다.
	int x = 0;
	for(int i = 0; i < num; i++) {
		FRIEND[i].I_length = ReadLen();
		fread(FRIEND[i].buffer,sizeof(char), FRIEND[i].I_length * 3 ,fp1);
		FRIEND[i].N_length = ReadLen();
		fread(FRIEND[i].buffer_n,sizeof(char), FRIEND[i].N_length *3 ,fp1);
		fread(FRIEND[i].buffer_g,sizeof(char),3,fp1);
		fread(FRIEND[i].buffer_age,sizeof(char),3,fp1);
	}
}
void FRIEND_SAVE() { // buffer에 있는 정보를 걸러서 출력하고자하는 구조체에 저장
	for(int i = 0; i < 3; i++) {
		Checkstr_I(FRIEND[i].buffer,i);
		Checkstr_N(FRIEND[i].buffer_n,i);
		FRIEND[i].gender = checkChar(FRIEND[i].buffer_g);
		FRIEND[i].age = checkChar(FRIEND[i].buffer_age);	
	}
}

void fprint() {
	fprintf(fp2,"*FRIENDS LIST*\n");
	for(int i = 0; i<num; i++) {
		fprintf(fp2,"FRIEND%d ID: %s\n",i+1,FRIEND[i].ID);
		fprintf(fp2,"FRIEND%d NAME: %s\n",i+1,FRIEND[i].name);
		if(FRIEND[i].gender=='M') {
			fprintf(fp2,"FRIEND%d GENDER: MALE\n",i+1);
		}
		else {
			fprintf(fp2,"FRIEND%d GENDER: FEMALE\n",i+1);
		}
		fprintf(fp2,"FRIEND%d AGE : %d\n\n",i+1,FRIEND[i].age);
	}
}



// 피피티 순서에 해당하는 문자열 이차원으로 선언
char* ITEM_NAME[] = {
    "BOMB",
    "POSTION",
    "CURE",
    "BOOK",
    "SHIELD",
    "CANNON"
};

// USER_STATUS_fun 변수

// ITEMS_fun 변수
unsigned char ITEMS_sort, ITEMS_count, ITEMS_num;
// FRIENDS LIST 변수

// Description

// main 함수
int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("error\n");
        return 0;
    }

    modified = argv[1];
    final_result = argv[2];
    fp1 = fopen(modified, "rb");
    fp2 = fopen(final_result, "w+t");

    // 유저 정보 출력
	Write_USER_STATUS();
//	Write_ITEMS();

	FRIEND_READ();
	FRIEND_SAVE();
	print();
	fprint();

    fclose(fp1);
    fclose(fp2);

    return 0;
}
// USER_STATUS 정보를 파일에 쓰는 함수
void Write_USER_STATUS(void) {
    unsigned char tmpLen;		//문자열 길이를 받아올 변수
    fprintf(fp2, "*USER STATUS*\n");

    tmpLen = ReadLen();		// ID의 길이를 읽음
    ReadStr(tmpLen, "ID");		// ID길이만큼 ID 읽음

    tmpLen = ReadLen();		// 이름의 길이를 읽음
    ReadStr(tmpLen, "NAME");		// 이름의 길이만큼 이름을 읽음

    tmpLen = ReadLen();		// 성별을 읽고 출력함
    if (tmpLen == 'M')
        fprintf(fp2, "GENDER: MALE\n");
    else if (tmpLen == 'F')
        fprintf(fp2, "GENDER: FEMALE\n");

    tmpLen = ReadLen();		// 나이를 읽고 출력함
    fprintf(fp2, "AGE: %d\n", tmpLen);

    tmpLen = ReadLen();		// HP를 읽고 출력함
    fprintf(fp2, "HP: %d\n", tmpLen);

    tmpLen = ReadLen();		// MP를 읽고 출력함
    fprintf(fp2, "MP: %d\n", tmpLen);

    unsigned short tmp = ReadShort();	// Coin을 읽고 출력함
    fprintf(fp2, "COIN: %d\n", tmp);

    fprintf(fp2, "\n");
}
// ITEMS 정보를 파일에 쓰는 함수
void Write_ITEMS(void) {
    ITEMS_sort = ReadLen();
    ITEMS_count = ReadLen();
    fprintf(fp2, "*ITEMS*\n");

    // sort가 0이면 순서대로
    if (ITEMS_sort == 0) {
        if ((ITEMS_count >= 1) && (ITEMS_count <= 4)) { // ITEMS 갯수가 1이상 4이하일때
            char ITEMS[6];
            int T_num = ReadLen(), n = 6;
            while (n != 0) {
                ITEMS[--n] = T_num % 2;
                T_num /= 2;
            }
            for (int i = 0; i < 6; i++) {
                if (ITEMS[i] != 0) {
                    ITEMS_num = ReadLen();
                    fprintf(fp2, "%s : %d\n", ITEM_NAME[i], ITEMS_num);
                }
                else
                    continue;
            }
        }
        else if ((ITEMS_count >= 5) && (ITEMS_count <= 6)) { // ITEMS 갯수가 5이상 6이하일때
            unsigned char ITEMS[6];   // 배열의 크기는 6으로 고정
            for (int i = 0; i < 6; i++) {
                ITEMS[i] = ReadLen();   // 차례대로 규칙해소
                if (ITEMS[i] == 0) // ITEMS배열에 저장된 수가 0이면 출력 x
                    continue;
                fprintf(fp2, "%s : %d\n", ITEM_NAME[i], ITEMS[i]);
            }
        }
    }

    // sort가 1이면 순서대로x
    else if (ITEMS_sort == 1) {
        char ITEMS[ITEMS_count * 2];    // 배열의 크기를 총 갯수 * 2로 고정
        for (int i = 0; i < ITEMS_count * 2; i++)
            ITEMS[i] = ReadLen();

        for (int j = 0; j < ITEMS_count * 2; j++) {
            fprintf(fp2, "%s : ", ITEM_NAME[ITEMS[j]]);
            fprintf(fp2, "%d\n", ITEMS[++j]);
        }
    }
    fprintf(fp2, "\n");
}

// 여기서부터는 언이가 코딩한 규칙해소 함수들
char CheckChar(char* tmp)      // tmp 가 KKK 이면
{
    char real;

    if (tmp[0] != tmp[1])   // tmp[0] K랑 tmp[1] K가 같은지 비교
    {
        if (tmp[0] != tmp[2])   // 0이랑 1이 틀다면 0이랑 2가 같은지 비교
        {
            if (tmp[1] == tmp[2])   // 같다면 1이랑 2, 2개가 같기때문에
            {
                real = tmp[1];   // real에 tmp중 1이나 2 아무거나 넣어서 리턴   (XKK) 의 경우
            }
            else
            {
               // printf("셋다 틀림");
				real = tmp[1];
            }
        }
        else   // 0이랑 2가 같다면 real에 0을 넣어서 리턴 (KXK) 의 경우
        {
            real = tmp[0];
        }
    }
    else
    {
        real = tmp[0];   // 0이랑 1이 같으니 (KKX)의 경우
    }

    return real;
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

char ReadLen() {	// Check 함수 먼저 읽으3 {
    char len[3];
    unsigned char m_len;

    for (int t = 0; t < 3; t++)
        fread(&len[t], sizeof(unsigned char), 1, fp1);	// ID길이 3개 읽어옴

    m_len = CheckChar(&len[0]);	// 읽어온 ID길이 3개를 Check 함수로 보내서 복원시킴 (667 을 보내면 6이 리턴됨)	

    return m_len;
}

void ReadStr(char len, char* target) {
    unsigned char str[255] = " ";

    for (int p = 0; p < len; p++) {
        char temp[3];

        for (int k = 0; k < 3; k++)
            fread(&temp[k], sizeof(unsigned char), 1, fp1);

        char a = CheckChar(&temp[0]);
        str[p] = a;
    }
    fprintf(fp2, "%s: %s\n", target, str);
}
