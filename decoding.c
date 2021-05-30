#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 255
char* fName;
char* str1 = "BOMB";
char* str2 = "POSTION";
char* str3 = "CURE";
char* str4 = "BOOK";
char* str5 = "SHIELD";
char* str6 = "CANNON";
// 파일포인터 선언
FILE* fp;
// USER_STATUS 변수들
unsigned char ID_length, Name_length, HP, MP;
char ID[MAX], NAME[MAX];
char GENDER, age;
unsigned short Coin;
// ITEMS 변수들
unsigned char ITEMS_num, ITEMS_amount;
// FRIENDS LIST
unsigned char FRIEND_ID_length, FRIEND_Name_length;
char gender, age;
char ID[MAX], NAME[MAX];
// Description

// 변수들
unsigned char tmpLen;
// 함수들
char ReadLen(char* target);
char Check(char* len);
void ITEMS(void);

// main 함수
int main(int argc, char* argv[]) {
    if (argc != 2)
    {
        printf("error\n");
        return 0;
    }

    fName = argv[1];
    fp = fopen(fName, "rb");

    ITEMS();
    return 0;
}

void ITEMS(void) {
    unsigned char sort, num, count;

    sort = ReadLen("순서 인지");
    printf("%d", sort);
    //// sort가 1이면 순서대로
    //if (sort == 1) {
    //    
    //}

    //// sort가 0이면 순서대로x
    //else if (sort == 0) {

    //}
}

char ReadLen(char* target)	// Check 함수 먼저 읽으3
{
    char len[3];
    unsigned char m_len;

    for (int t = 0; t < 3; t++) {
        fread(&len[t], sizeof(unsigned char), 1, fp);	// ID길이 3개 읽어옴
    }

    m_len = Check(&len[0]);	// 읽어온 ID길이 3개를 Check 함수로 보내서 복원시킴 (667 을 보내면 6이 리턴됨)	

    return m_len;
}


char Check(char* tmp)      // tmp 가 KKK 이면
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
                printf("셋다 틀림");
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
