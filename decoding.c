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
// ���������� ����
FILE* fp;
// USER_STATUS ������
unsigned char ID_length, Name_length, HP, MP;
char ID[MAX], NAME[MAX];
char GENDER, age;
unsigned short Coin;
// ITEMS ������
unsigned char ITEMS_num, ITEMS_amount;
// FRIENDS LIST
unsigned char FRIEND_ID_length, FRIEND_Name_length;
char gender, age;
char ID[MAX], NAME[MAX];
// Description

// ������
unsigned char tmpLen;
// �Լ���
char ReadLen(char* target);
char Check(char* len);
void ITEMS(void);

// main �Լ�
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

    sort = ReadLen("���� ����");
    printf("%d", sort);
    //// sort�� 1�̸� �������
    //if (sort == 1) {
    //    
    //}

    //// sort�� 0�̸� �������x
    //else if (sort == 0) {

    //}
}

char ReadLen(char* target)	// Check �Լ� ���� ����3
{
    char len[3];
    unsigned char m_len;

    for (int t = 0; t < 3; t++) {
        fread(&len[t], sizeof(unsigned char), 1, fp);	// ID���� 3�� �о��
    }

    m_len = Check(&len[0]);	// �о�� ID���� 3���� Check �Լ��� ������ ������Ŵ (667 �� ������ 6�� ���ϵ�)	

    return m_len;
}


char Check(char* tmp)      // tmp �� KKK �̸�
{
    char real;

    if (tmp[0] != tmp[1])   // tmp[0] K�� tmp[1] K�� ������ ��
    {
        if (tmp[0] != tmp[2])   // 0�̶� 1�� Ʋ�ٸ� 0�̶� 2�� ������ ��
        {
            if (tmp[1] == tmp[2])   // ���ٸ� 1�̶� 2, 2���� ���⶧����
            {
                real = tmp[1];   // real�� tmp�� 1�̳� 2 �ƹ��ų� �־ ����   (XKK) �� ���
            }
            else
            {
                printf("�´� Ʋ��");
            }
        }
        else   // 0�̶� 2�� ���ٸ� real�� 0�� �־ ���� (KXK) �� ���
        {
            real = tmp[0];
        }
    }
    else
    {
        real = tmp[0];   // 0�̶� 1�� ������ (KKX)�� ���
    }

    return real;
}
