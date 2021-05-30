#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 255
char* fName;

char* ITEM_NAME[] = {
    "BOMB",
    "POSTION",
    "CURE",
    "BOOK",
    "SHIELD",
    "CANNON"
};
// 파일포인터 선언
FILE* fp;
// USER_STATUS 변수들
unsigned char ID_length, Name_length, HP, MP;
char ID[MAX], NAME[MAX];
char GENDER, age;
unsigned short Coin;
// ITEMS 변수들
unsigned char ITEMS_sort, ITEMS_count, ITEMS_num;
// FRIENDS LIST
char FRIEND_ID_length, FRIEND_Name_length;
char gender, age;
char ID[MAX], NAME[MAX];
// Description

// 변수들
unsigned char tmpLen;
// 함수들
char ReadLen(void);
char Check(char* len);
void ITEM_fun(void);

// main 함수
int main(int argc, char* argv[]) {
    if (argc != 2)
    {
        printf("error\n");
        return 0;
    }

    fName = argv[1];
    fp = fopen(fName, "rb");
    ITEM_fun();
    return 0;
}

void ITEM_fun(void) {
    ITEMS_sort = ReadLen();
    ITEMS_count = ReadLen();
    printf("*ITEMS*\n");

    // sort가 1이면 순서대로
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
                    printf("%s : %d\n", ITEM_NAME[i], ITEMS_num);
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
                printf("%s : %d\n", ITEM_NAME[i], ITEMS[i]);
            }
        }
    }

    // sort가 0이면 순서대로x
    else if (ITEMS_sort == 1) {
        char ITEMS[ITEMS_count * 2];    // 배열의 크기를 총 갯수 * 2로 고정
        for (int i = 0; i < ITEMS_count * 2; i++)
            ITEMS[i] = ReadLen(); 

        for (int j = 0; j < ITEMS_count * 2; j++) {
            printf("%s : ", ITEM_NAME[ITEMS[j]]);
            printf("%d\n", ITEMS[++j]);
        }
    }
    printf("\n");
}

char ReadLen()	// Check 함수 먼저 읽으3
{
    char len[3];
    unsigned char m_len;

    for (int t = 0; t < 3; t++)
        fread(&len[t], sizeof(unsigned char), 1, fp);	// ID길이 3개 읽어옴

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
