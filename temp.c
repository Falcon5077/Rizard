#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 255
char* fName;

<<<<<<< HEAD
// ÇÇÇÇÆ¼ ¼ø¼­¿¡ ÇØ´çÇÏ´Â ¹®ÀÚ¿­ ÀÌÂ÷¿øÀ¸·Î ¼±¾ð
=======
// í”¼í”¼í‹° ìˆœì„œì— í•´ë‹¹í•˜ëŠ” ë¬¸ìžì—´ ì´ì°¨ì›ìœ¼ë¡œ ì„ ì–¸
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
// ÆÄÀÏÆ÷ÀÎÅÍ ¼±¾ð
FILE* fp;
// USER_STATUS_fun º¯¼ö
unsigned char tmpLen;
// ITEMS_fun º¯¼ö
unsigned char ITEMS_sort, ITEMS_count, ITEMS_num;
// FRIENDS LIST º¯¼ö

// Description

// ±ÔÄ¢ÇØ¼Ò ÇÔ¼öµé
=======
// íŒŒì¼í¬ì¸í„° ì„ ì–¸
FILE* fp;
// USER_STATUS_fun ë³€ìˆ˜
unsigned char tmpLen;
// ITEMS_fun ë³€ìˆ˜
unsigned char ITEMS_sort, ITEMS_count, ITEMS_num;
// FRIENDS LIST ë³€ìˆ˜

// Description

// ê·œì¹™í•´ì†Œ í•¨ìˆ˜ë“¤
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
char CheckChar(char* len);
unsigned short CheckShort(unsigned short* tmp); 
char ReadLen(void);
unsigned short ReadShort();
void ReadStr(char len, char* target);
<<<<<<< HEAD
// ÅØ½ºÆ® Ãâ·Â ÇÔ¼ö
void USER_STATUS_fun(void);
void ITEM_fun(void);

// main ÇÔ¼ö
=======
// í…ìŠ¤íŠ¸ ì¶œë ¥ í•¨ìˆ˜
void USER_STATUS_fun(void);
void ITEM_fun(void);

// main í•¨ìˆ˜
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
    // À¯Àú Á¤º¸ Ãâ·Â
    USER_STATUS_fun();
    // ¾ÆÀÌÅÛ Á¤º¸ Ãâ·Â
=======
    // ìœ ì € ì •ë³´ ì¶œë ¥
    USER_STATUS_fun();
    // ì•„ì´í…œ ì •ë³´ ì¶œë ¥
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
    ITEM_fun();

    return 0;
}
<<<<<<< HEAD
// USER_STATUS Ãâ·ÂÇÔ¼ö
void USER_STATUS_fun(void) {
    unsigned char tmpLen;		//¹®ÀÚ¿­ ±æÀÌ¸¦ ¹Þ¾Æ¿Ã º¯¼ö

    printf("*User STATUS*\n");

    tmpLen = ReadLen();		// IDÀÇ ±æÀÌ¸¦ ÀÐÀ½
    ReadStr(tmpLen, "ID");		// ID±æÀÌ¸¸Å­ ID ÀÐÀ½

    tmpLen = ReadLen();		// ÀÌ¸§ÀÇ ±æÀÌ¸¦ ÀÐÀ½
    ReadStr(tmpLen, "NAME");		// ÀÌ¸§ÀÇ ±æÀÌ¸¸Å­ ÀÌ¸§À» ÀÐÀ½

    tmpLen = ReadLen();		// ¼ºº°À» ÀÐ°í Ãâ·ÂÇÔ
=======
// USER_STATUS ì¶œë ¥í•¨ìˆ˜
void USER_STATUS_fun(void) {
    unsigned char tmpLen;		//ë¬¸ìžì—´ ê¸¸ì´ë¥¼ ë°›ì•„ì˜¬ ë³€ìˆ˜

    printf("*User STATUS*\n");

    tmpLen = ReadLen();		// IDì˜ ê¸¸ì´ë¥¼ ì½ìŒ
    ReadStr(tmpLen, "ID");		// IDê¸¸ì´ë§Œí¼ ID ì½ìŒ

    tmpLen = ReadLen();		// ì´ë¦„ì˜ ê¸¸ì´ë¥¼ ì½ìŒ
    ReadStr(tmpLen, "NAME");		// ì´ë¦„ì˜ ê¸¸ì´ë§Œí¼ ì´ë¦„ì„ ì½ìŒ

    tmpLen = ReadLen();		// ì„±ë³„ì„ ì½ê³  ì¶œë ¥í•¨
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
    if (tmpLen == 'M')
        printf("GENDER: MALE\n");
    if (tmpLen == 'F')
        printf("GENDER: FEMALE\n");

<<<<<<< HEAD
    tmpLen = ReadLen();		// ³ªÀÌ¸¦ ÀÐ°í Ãâ·ÂÇÔ
    printf("AGE: %d\n", tmpLen);

    tmpLen = ReadLen();		// HP¸¦ ÀÐ°í Ãâ·ÂÇÔ
    printf("HP: %d\n", tmpLen);

    tmpLen = ReadLen();		// MP¸¦ ÀÐ°í Ãâ·ÂÇÔ
    printf("MP: %d\n", tmpLen);

    unsigned short tmp = ReadShort();	// CoinÀ» ÀÐ°í Ãâ·ÂÇÔ
=======
    tmpLen = ReadLen();		// ë‚˜ì´ë¥¼ ì½ê³  ì¶œë ¥í•¨
    printf("AGE: %d\n", tmpLen);

    tmpLen = ReadLen();		// HPë¥¼ ì½ê³  ì¶œë ¥í•¨
    printf("HP: %d\n", tmpLen);

    tmpLen = ReadLen();		// MPë¥¼ ì½ê³  ì¶œë ¥í•¨
    printf("MP: %d\n", tmpLen);

    unsigned short tmp = ReadShort();	// Coinì„ ì½ê³  ì¶œë ¥í•¨
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
    printf("COIN: %d\n", tmp);

    printf("\n");
}
<<<<<<< HEAD
// ITEMS Ãâ·Â ÇÔ¼ö
=======
// ITEMS ì¶œë ¥ í•¨ìˆ˜
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
void ITEM_fun(void) {
    ITEMS_sort = ReadLen();
    ITEMS_count = ReadLen();
    printf("*ITEMS*\n");

<<<<<<< HEAD
    // sort°¡ 1ÀÌ¸é ¼ø¼­´ë·Î
    if (ITEMS_sort == 0) {
        if ((ITEMS_count >= 1) && (ITEMS_count <= 4)) { // ITEMS °¹¼ö°¡ 1ÀÌ»ó 4ÀÌÇÏÀÏ¶§
=======
    // sortê°€ 1ì´ë©´ ìˆœì„œëŒ€ë¡œ
    if (ITEMS_sort == 0) {
        if ((ITEMS_count >= 1) && (ITEMS_count <= 4)) { // ITEMS ê°¯ìˆ˜ê°€ 1ì´ìƒ 4ì´í•˜ì¼ë•Œ
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
        else if ((ITEMS_count >= 5) && (ITEMS_count <= 6)) { // ITEMS °¹¼ö°¡ 5ÀÌ»ó 6ÀÌÇÏÀÏ¶§
            unsigned char ITEMS[6];   // ¹è¿­ÀÇ Å©±â´Â 6À¸·Î °íÁ¤
            for (int i = 0; i < 6; i++) {
                ITEMS[i] = ReadLen();   // Â÷·Ê´ë·Î ±ÔÄ¢ÇØ¼Ò
                if (ITEMS[i] == 0) // ITEMS¹è¿­¿¡ ÀúÀåµÈ ¼ö°¡ 0ÀÌ¸é Ãâ·Â x
=======
        else if ((ITEMS_count >= 5) && (ITEMS_count <= 6)) { // ITEMS ê°¯ìˆ˜ê°€ 5ì´ìƒ 6ì´í•˜ì¼ë•Œ
            unsigned char ITEMS[6];   // ë°°ì—´ì˜ í¬ê¸°ëŠ” 6ìœ¼ë¡œ ê³ ì •
            for (int i = 0; i < 6; i++) {
                ITEMS[i] = ReadLen();   // ì°¨ë¡€ëŒ€ë¡œ ê·œì¹™í•´ì†Œ
                if (ITEMS[i] == 0) // ITEMSë°°ì—´ì— ì €ìž¥ëœ ìˆ˜ê°€ 0ì´ë©´ ì¶œë ¥ x
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
                    continue;
                printf("%s : %d\n", ITEM_NAME[i], ITEMS[i]);
            }
        }
    }

<<<<<<< HEAD
    // sort°¡ 0ÀÌ¸é ¼ø¼­´ë·Îx
    else if (ITEMS_sort == 1) {
        unsigned char ITEMS[ITEMS_count * 2];    // ¹è¿­ÀÇ Å©±â¸¦ ÃÑ °¹¼ö * 2·Î °íÁ¤
=======
    // sortê°€ 0ì´ë©´ ìˆœì„œëŒ€ë¡œx
    else if (ITEMS_sort == 1) {
        char ITEMS[ITEMS_count * 2];    // ë°°ì—´ì˜ í¬ê¸°ë¥¼ ì´ ê°¯ìˆ˜ * 2ë¡œ ê³ ì •
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
// ¿©±â¼­ºÎÅÍ´Â ¾ðÀÌ°¡ ÄÚµùÇÑ ±ÔÄ¢ÇØ¼Ò ÇÔ¼öµé
char CheckChar(char* tmp)      // tmp °¡ KKK ÀÌ¸é
{
    char real;

    if (tmp[0] != tmp[1])   // tmp[0] K¶û tmp[1] K°¡ °°ÀºÁö ºñ±³
    {
        if (tmp[0] != tmp[2])   // 0ÀÌ¶û 1ÀÌ Æ²´Ù¸é 0ÀÌ¶û 2°¡ °°ÀºÁö ºñ±³
        {
            if (tmp[1] == tmp[2])   // °°´Ù¸é 1ÀÌ¶û 2, 2°³°¡ °°±â¶§¹®¿¡
            {
                real = tmp[1];   // real¿¡ tmpÁß 1ÀÌ³ª 2 ¾Æ¹«°Å³ª ³Ö¾î¼­ ¸®ÅÏ   (XKK) ÀÇ °æ¿ì
            }
            else
            {
                printf("¼Â´Ù Æ²¸²");
            }
        }
        else   // 0ÀÌ¶û 2°¡ °°´Ù¸é real¿¡ 0À» ³Ö¾î¼­ ¸®ÅÏ (KXK) ÀÇ °æ¿ì
=======
// ì—¬ê¸°ì„œë¶€í„°ëŠ” ì–¸ì´ê°€ ì½”ë”©í•œ ê·œì¹™í•´ì†Œ í•¨ìˆ˜ë“¤
char CheckChar(char* tmp)      // tmp ê°€ KKK ì´ë©´
{
    char real;

    if (tmp[0] != tmp[1])   // tmp[0] Këž‘ tmp[1] Kê°€ ê°™ì€ì§€ ë¹„êµ
    {
        if (tmp[0] != tmp[2])   // 0ì´ëž‘ 1ì´ í‹€ë‹¤ë©´ 0ì´ëž‘ 2ê°€ ê°™ì€ì§€ ë¹„êµ
        {
            if (tmp[1] == tmp[2])   // ê°™ë‹¤ë©´ 1ì´ëž‘ 2, 2ê°œê°€ ê°™ê¸°ë•Œë¬¸ì—
            {
                real = tmp[1];   // realì— tmpì¤‘ 1ì´ë‚˜ 2 ì•„ë¬´ê±°ë‚˜ ë„£ì–´ì„œ ë¦¬í„´   (XKK) ì˜ ê²½ìš°
            }
            else
            {
                printf("ì…‹ë‹¤ í‹€ë¦¼");
            }
        }
        else   // 0ì´ëž‘ 2ê°€ ê°™ë‹¤ë©´ realì— 0ì„ ë„£ì–´ì„œ ë¦¬í„´ (KXK) ì˜ ê²½ìš°
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
        {
            real = tmp[0];
        }
    }
    else
    {
<<<<<<< HEAD
        real = tmp[0];   // 0ÀÌ¶û 1ÀÌ °°À¸´Ï (KKX)ÀÇ °æ¿ì
=======
        real = tmp[0];   // 0ì´ëž‘ 1ì´ ê°™ìœ¼ë‹ˆ (KKX)ì˜ ê²½ìš°
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
    }

    return real;
}

<<<<<<< HEAD
unsigned short CheckShort(unsigned short* tmp)		// tmp °¡ KKK ÀÌ¸é
{
    unsigned short real;

    if (tmp[0] != tmp[1])	// tmp[0] K¶û tmp[1] K°¡ °°ÀºÁö ºñ±³
    {
        if (tmp[0] != tmp[2])	// 0ÀÌ¶û 1ÀÌ Æ²´Ù¸é 0ÀÌ¶û 2°¡ °°ÀºÁö ºñ±³
        {
            if (tmp[1] == tmp[2])	// °°´Ù¸é 1ÀÌ¶û 2, 2°³°¡ °°±â¶§¹®¿¡
            {
                real = tmp[1];	// real¿¡ tmpÁß 1ÀÌ³ª 2 ¾Æ¹«°Å³ª ³Ö¾î¼­ ¸®ÅÏ	(XKK) ÀÇ °æ¿ì
            }
            else
            {
                printf("¼Â´Ù Æ²¸² ");
            }
        }
        else	// 0ÀÌ¶û 2°¡ °°´Ù¸é real¿¡ 0À» ³Ö¾î¼­ ¸®ÅÏ (KXK) ÀÇ °æ¿ì
=======
unsigned short CheckShort(unsigned short* tmp)		// tmp ê°€ KKK ì´ë©´
{
    unsigned short real;

    if (tmp[0] != tmp[1])	// tmp[0] Këž‘ tmp[1] Kê°€ ê°™ì€ì§€ ë¹„êµ
    {
        if (tmp[0] != tmp[2])	// 0ì´ëž‘ 1ì´ í‹€ë‹¤ë©´ 0ì´ëž‘ 2ê°€ ê°™ì€ì§€ ë¹„êµ
        {
            if (tmp[1] == tmp[2])	// ê°™ë‹¤ë©´ 1ì´ëž‘ 2, 2ê°œê°€ ê°™ê¸°ë•Œë¬¸ì—
            {
                real = tmp[1];	// realì— tmpì¤‘ 1ì´ë‚˜ 2 ì•„ë¬´ê±°ë‚˜ ë„£ì–´ì„œ ë¦¬í„´	(XKK) ì˜ ê²½ìš°
            }
            else
            {
                printf("ì…‹ë‹¤ í‹€ë¦¼ ");
            }
        }
        else	// 0ì´ëž‘ 2ê°€ ê°™ë‹¤ë©´ realì— 0ì„ ë„£ì–´ì„œ ë¦¬í„´ (KXK) ì˜ ê²½ìš°
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
        {
            real = tmp[0];
        }
    }
    else
    {
<<<<<<< HEAD
        real = tmp[0];	// 0ÀÌ¶û 1ÀÌ °°À¸´Ï (KKX)ÀÇ °æ¿ì
=======
        real = tmp[0];	// 0ì´ëž‘ 1ì´ ê°™ìœ¼ë‹ˆ (KKX)ì˜ ê²½ìš°
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
char ReadLen() {	// Check ÇÔ¼ö ¸ÕÀú ÀÐÀ¸3 {
=======
char ReadLen() {	// Check í•¨ìˆ˜ ë¨¼ì € ì½ìœ¼3 {
>>>>>>> 4c2dc3c42589375277838d8ad9eb93ea90218c0b
    char len[3];
    unsigned char m_len;

    for (int t = 0; t < 3; t++)
<<<<<<< HEAD
        fread(&len[t], sizeof(unsigned char), 1, fp);	// ID±æÀÌ 3°³ ÀÐ¾î¿È

    m_len = CheckChar(&len[0]);	// ÀÐ¾î¿Â ID±æÀÌ 3°³¸¦ Check ÇÔ¼ö·Î º¸³»¼­ º¹¿ø½ÃÅ´ (667 À» º¸³»¸é 6ÀÌ ¸®ÅÏµÊ)	
=======
        fread(&len[t], sizeof(unsigned char), 1, fp);	// IDê¸¸ì´ 3ê°œ ì½ì–´ì˜´

    m_len = CheckChar(&len[0]);	// ì½ì–´ì˜¨ IDê¸¸ì´ 3ê°œë¥¼ Check í•¨ìˆ˜ë¡œ ë³´ë‚´ì„œ ë³µì›ì‹œí‚´ (667 ì„ ë³´ë‚´ë©´ 6ì´ ë¦¬í„´ë¨)	
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
