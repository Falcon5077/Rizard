#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 255
char* fName;

<<<<<<< HEAD
// 피피티 순서에 해당하는 문자열 이차원으로 선언
=======
// �뵾�뵾�떚 �닚�꽌�뿉 �빐�떦�븯�뒗 臾몄옄�뿴 �씠李⑥썝�쑝濡� �꽑�뼵
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
char* ITEM_NAME[] = {
    "BOMB",
    "POSTION",
    "CURE",
    "BOOK",
    "SHIELD",
    "CANNON"
};
<<<<<<< HEAD
// 파일포인터 선언
FILE* fp;
// USER_STATUS_fun 변수
unsigned char tmpLen;
// ITEMS_fun 변수
unsigned char ITEMS_sort, ITEMS_count, ITEMS_num;
// FRIENDS LIST 변수

// Description

// 규칙해소 함수들
=======
// �뙆�씪�룷�씤�꽣 �꽑�뼵
FILE* fp;
// USER_STATUS_fun 蹂��닔
unsigned char tmpLen;
// ITEMS_fun 蹂��닔
unsigned char ITEMS_sort, ITEMS_count, ITEMS_num;
// FRIENDS LIST 蹂��닔

// Description

// 洹쒖튃�빐�냼 �븿�닔�뱾
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
char CheckChar(char* len);
unsigned short CheckShort(unsigned short* tmp); 
char ReadLen(void);
unsigned short ReadShort();
void ReadStr(char len, char* target);
<<<<<<< HEAD
// 텍스트 출력 함수
void USER_STATUS_fun(void);
void ITEM_fun(void);

// main 함수
=======
// �뀓�뒪�듃 異쒕젰 �븿�닔
void USER_STATUS_fun(void);
void ITEM_fun(void);

// main �븿�닔
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
int main(int argc, char* argv[]) {
    if (argc != 2)
    {
        printf("error\n");
        return 0;
    }

    fName = argv[1];
    fp = fopen(fName, "rb");
<<<<<<< HEAD
    // 유저 정보 출력
    USER_STATUS_fun();
    // 아이템 정보 출력
=======
    // �쑀��� �젙蹂� 異쒕젰
    USER_STATUS_fun();
    // �븘�씠�뀥 �젙蹂� 異쒕젰
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
    ITEM_fun();

    return 0;
}
<<<<<<< HEAD
// USER_STATUS 출력함수
void USER_STATUS_fun(void) {
    unsigned char tmpLen;		//문자열 길이를 받아올 변수

    printf("*User STATUS*\n");

    tmpLen = ReadLen();		// ID의 길이를 읽음
    ReadStr(tmpLen, "ID");		// ID길이만큼 ID 읽음

    tmpLen = ReadLen();		// 이름의 길이를 읽음
    ReadStr(tmpLen, "NAME");		// 이름의 길이만큼 이름을 읽음

    tmpLen = ReadLen();		// 성별을 읽고 출력함
=======
// USER_STATUS 異쒕젰�븿�닔
void USER_STATUS_fun(void) {
    unsigned char tmpLen;		//臾몄옄�뿴 湲몄씠瑜� 諛쏆븘�삱 蹂��닔

    printf("*User STATUS*\n");

    tmpLen = ReadLen();		// ID�쓽 湲몄씠瑜� �씫�쓬
    ReadStr(tmpLen, "ID");		// ID湲몄씠留뚰겮 ID �씫�쓬

    tmpLen = ReadLen();		// �씠由꾩쓽 湲몄씠瑜� �씫�쓬
    ReadStr(tmpLen, "NAME");		// �씠由꾩쓽 湲몄씠留뚰겮 �씠由꾩쓣 �씫�쓬

    tmpLen = ReadLen();		// �꽦蹂꾩쓣 �씫怨� 異쒕젰�븿
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
    if (tmpLen == 'M')
        printf("GENDER: MALE\n");
    if (tmpLen == 'F')
        printf("GENDER: FEMALE\n");

<<<<<<< HEAD
    tmpLen = ReadLen();		// 나이를 읽고 출력함
    printf("AGE: %d\n", tmpLen);

    tmpLen = ReadLen();		// HP를 읽고 출력함
    printf("HP: %d\n", tmpLen);

    tmpLen = ReadLen();		// MP를 읽고 출력함
    printf("MP: %d\n", tmpLen);

    unsigned short tmp = ReadShort();	// Coin을 읽고 출력함
=======
    tmpLen = ReadLen();		// �굹�씠瑜� �씫怨� 異쒕젰�븿
    printf("AGE: %d\n", tmpLen);

    tmpLen = ReadLen();		// HP瑜� �씫怨� 異쒕젰�븿
    printf("HP: %d\n", tmpLen);

    tmpLen = ReadLen();		// MP瑜� �씫怨� 異쒕젰�븿
    printf("MP: %d\n", tmpLen);

    unsigned short tmp = ReadShort();	// Coin�쓣 �씫怨� 異쒕젰�븿
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
    printf("COIN: %d\n", tmp);

    printf("\n");
}
<<<<<<< HEAD
// ITEMS 출력 함수
=======
// ITEMS 異쒕젰 �븿�닔
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
void ITEM_fun(void) {
    ITEMS_sort = ReadLen();
    ITEMS_count = ReadLen();
    printf("*ITEMS*\n");

<<<<<<< HEAD
    // sort가 1이면 순서대로
    if (ITEMS_sort == 0) {
        if ((ITEMS_count >= 1) && (ITEMS_count <= 4)) { // ITEMS 갯수가 1이상 4이하일때
=======
    // sort媛� 1�씠硫� �닚�꽌���濡�
    if (ITEMS_sort == 0) {
        if ((ITEMS_count >= 1) && (ITEMS_count <= 4)) { // ITEMS 媛��닔媛� 1�씠�긽 4�씠�븯�씪�븣
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
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
<<<<<<< HEAD
        else if ((ITEMS_count >= 5) && (ITEMS_count <= 6)) { // ITEMS 갯수가 5이상 6이하일때
            unsigned char ITEMS[6];   // 배열의 크기는 6으로 고정
            for (int i = 0; i < 6; i++) {
                ITEMS[i] = ReadLen();   // 차례대로 규칙해소
                if (ITEMS[i] == 0) // ITEMS배열에 저장된 수가 0이면 출력 x
=======
        else if ((ITEMS_count >= 5) && (ITEMS_count <= 6)) { // ITEMS 媛��닔媛� 5�씠�긽 6�씠�븯�씪�븣
            unsigned char ITEMS[6];   // 諛곗뿴�쓽 �겕湲곕뒗 6�쑝濡� 怨좎젙
            for (int i = 0; i < 6; i++) {
                ITEMS[i] = ReadLen();   // 李⑤�����濡� 洹쒖튃�빐�냼
                if (ITEMS[i] == 0) // ITEMS諛곗뿴�뿉 ����옣�맂 �닔媛� 0�씠硫� 異쒕젰 x
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
                    continue;
                printf("%s : %d\n", ITEM_NAME[i], ITEMS[i]);
            }
        }
    }

<<<<<<< HEAD
    // sort가 0이면 순서대로x
    else if (ITEMS_sort == 1) {
        unsigned char ITEMS[ITEMS_count * 2];    // 배열의 크기를 총 갯수 * 2로 고정
=======
    // sort媛� 0�씠硫� �닚�꽌���濡쐘
    else if (ITEMS_sort == 1) {
        char ITEMS[ITEMS_count * 2];    // 諛곗뿴�쓽 �겕湲곕�� 珥� 媛��닔 * 2濡� 怨좎젙
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
        for (int i = 0; i < ITEMS_count * 2; i++)
            ITEMS[i] = ReadLen(); 

        for (int j = 0; j < ITEMS_count * 2; j++) {
            printf("%s : ", ITEM_NAME[ITEMS[j]]);
            printf("%d\n", ITEMS[++j]);
        }
    }
    printf("\n");
}

<<<<<<< HEAD
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
                printf("셋다 틀림");
            }
        }
        else   // 0이랑 2가 같다면 real에 0을 넣어서 리턴 (KXK) 의 경우
=======
// �뿬湲곗꽌遺��꽣�뒗 �뼵�씠媛� 肄붾뵫�븳 洹쒖튃�빐�냼 �븿�닔�뱾
char CheckChar(char* tmp)      // tmp 媛� KKK �씠硫�
{
    char real;

    if (tmp[0] != tmp[1])   // tmp[0] K�옉 tmp[1] K媛� 媛숈��吏� 鍮꾧탳
    {
        if (tmp[0] != tmp[2])   // 0�씠�옉 1�씠 ����떎硫� 0�씠�옉 2媛� 媛숈��吏� 鍮꾧탳
        {
            if (tmp[1] == tmp[2])   // 媛숇떎硫� 1�씠�옉 2, 2媛쒓�� 媛숆린�븣臾몄뿉
            {
                real = tmp[1];   // real�뿉 tmp以� 1�씠�굹 2 �븘臾닿굅�굹 �꽔�뼱�꽌 由ы꽩   (XKK) �쓽 寃쎌슦
            }
            else
            {
                printf("�뀑�떎 ���由�");
            }
        }
        else   // 0�씠�옉 2媛� 媛숇떎硫� real�뿉 0�쓣 �꽔�뼱�꽌 由ы꽩 (KXK) �쓽 寃쎌슦
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
        {
            real = tmp[0];
        }
    }
    else
    {
<<<<<<< HEAD
        real = tmp[0];   // 0이랑 1이 같으니 (KKX)의 경우
=======
        real = tmp[0];   // 0�씠�옉 1�씠 媛숈쑝�땲 (KKX)�쓽 寃쎌슦
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
    }

    return real;
}

<<<<<<< HEAD
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
                printf("셋다 틀림 ");
            }
        }
        else	// 0이랑 2가 같다면 real에 0을 넣어서 리턴 (KXK) 의 경우
=======
unsigned short CheckShort(unsigned short* tmp)		// tmp 媛� KKK �씠硫�
{
    unsigned short real;

    if (tmp[0] != tmp[1])	// tmp[0] K�옉 tmp[1] K媛� 媛숈��吏� 鍮꾧탳
    {
        if (tmp[0] != tmp[2])	// 0�씠�옉 1�씠 ����떎硫� 0�씠�옉 2媛� 媛숈��吏� 鍮꾧탳
        {
            if (tmp[1] == tmp[2])	// 媛숇떎硫� 1�씠�옉 2, 2媛쒓�� 媛숆린�븣臾몄뿉
            {
                real = tmp[1];	// real�뿉 tmp以� 1�씠�굹 2 �븘臾닿굅�굹 �꽔�뼱�꽌 由ы꽩	(XKK) �쓽 寃쎌슦
            }
            else
            {
                printf("�뀑�떎 ���由� ");
            }
        }
        else	// 0�씠�옉 2媛� 媛숇떎硫� real�뿉 0�쓣 �꽔�뼱�꽌 由ы꽩 (KXK) �쓽 寃쎌슦
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
        {
            real = tmp[0];
        }
    }
    else
    {
<<<<<<< HEAD
        real = tmp[0];	// 0이랑 1이 같으니 (KKX)의 경우
=======
        real = tmp[0];	// 0�씠�옉 1�씠 媛숈쑝�땲 (KKX)�쓽 寃쎌슦
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
    }

    return real;
}

unsigned short ReadShort() {
    unsigned short len[3];
    unsigned short m_short;

    for (int t = 0; t < 3; t++)
        fread(&len[t], sizeof(unsigned short), 1, fp);

    m_short = CheckShort(&len[0]);

    return m_short;
}

<<<<<<< HEAD
char ReadLen() {	// Check 함수 먼저 읽으3 {
=======
char ReadLen() {	// Check �븿�닔 癒쇱�� �씫�쑝3 {
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
    char len[3];
    unsigned char m_len;

    for (int t = 0; t < 3; t++)
<<<<<<< HEAD
        fread(&len[t], sizeof(unsigned char), 1, fp);	// ID길이 3개 읽어옴

    m_len = CheckChar(&len[0]);	// 읽어온 ID길이 3개를 Check 함수로 보내서 복원시킴 (667 을 보내면 6이 리턴됨)	
=======
        fread(&len[t], sizeof(unsigned char), 1, fp);	// ID湲몄씠 3媛� �씫�뼱�샂

    m_len = CheckChar(&len[0]);	// �씫�뼱�삩 ID湲몄씠 3媛쒕�� Check �븿�닔濡� 蹂대궡�꽌 蹂듭썝�떆�궡 (667 �쓣 蹂대궡硫� 6�씠 由ы꽩�맖)	
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b

    return m_len;
}

void ReadStr(char len, char* target) {
    unsigned char str[255] = " ";

    for (int p = 0; p < len; p++) {
        char temp[3];

        for (int k = 0; k < 3; k++)
            fread(&temp[k], sizeof(unsigned char), 1, fp);

        char a = CheckChar(&temp[0]);
        str[p] = a;
    }
    printf("%s: %s\n", target, str);
}
