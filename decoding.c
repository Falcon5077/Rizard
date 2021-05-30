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
// ���������� ����
FILE* fp;
// ITEMS ������
unsigned char ITEMS_sort, ITEMS_count, ITEMS_num;
// �Լ���
char ReadLen(void);
char Check(char* len);
void ITEM_fun(void);

// main �Լ�
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

    // sort�� 1�̸� �������
    if (ITEMS_sort == 0) {
        if ((ITEMS_count >= 1) && (ITEMS_count <= 4)) { // ITEMS ������ 1�̻� 4�����϶�
            char ITEMS[6];
            int T_num = ReadLen(), n = 6;		// T_num�� �������� ������ 1�� 0���� ǥ���� 2������ 10������ ��ȯ�� ������ ���� �� �ʱ�ȭ
            while (n != 0) {
                ITEMS[--n] = T_num % 2;	// 10������ 2������ ��ȯ�Ͽ� ITEMS �迭�� ����, [5--] ���·� �ڿ������� ����
                T_num /= 2; 
            }
            for (int i = 0; i < 6; i++) {
                if (ITEMS[i] != 0) { 
                    ITEMS_num = ReadLen(); // ������ �ҷ��ͼ� ITEMS_num�� ���� �� 
                    printf("%s : %d\n", ITEM_NAME[i], ITEMS_num); // �̸��� �Բ� ���
                }
                else
                    continue;
            }
        }
        else if ((ITEMS_count >= 5) && (ITEMS_count <= 6)) { // ITEMS ������ 5�̻� 6�����϶�
            unsigned char ITEMS[6];   // �迭�� ũ��� 6���� ����
            for (int i = 0; i < 6; i++) {
                ITEMS[i] = ReadLen();   // ���ʴ�� ��Ģ�ؼ�
                if (ITEMS[i] == 0) // ITEMS�迭�� ����� ���� 0�̸� ��� x
                    continue;
                printf("%s : %d\n", ITEM_NAME[i], ITEMS[i]);
            }
        }
    }

    // sort�� 0�̸� �������x
    else if (ITEMS_sort == 1) {
        char ITEMS[ITEMS_count * 2];    // �迭�� ũ�⸦ �� ���� * 2�� ����
        for (int i = 0; i < ITEMS_count * 2; i++)
            ITEMS[i] = ReadLen(); // ITEMS�迭�� ���Ͽ� ����� ������ ���� ����  ��Ģ�ؼҿ� �Բ� ����

        for (int j = 0; j < ITEMS_count * 2; j++) {
            printf("%s : ", ITEM_NAME[ITEMS[j]]); // ������ �̸��� �Բ� 
            printf("%d\n", ITEMS[++j]); // ������ ���� ���
        }
    }
    printf("\n");
}

// ���⼭���ʹ� ���� ��Ģ�ؼ� �Լ� �����Ͽ���
char ReadLen()	// Check �Լ� ���� ����3
{
    char len[3];
    unsigned char m_len;

    for (int t = 0; t < 3; t++)
        fread(&len[t], sizeof(unsigned char), 1, fp);	// ID���� 3�� �о��

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
