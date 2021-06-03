#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

typedef struct User_Status {
        unsigned char *id;
        unsigned char *name;
        unsigned char *gender;
        char *age;
        char *HP;
        char *MP;
        unsigned short *coin;
} User_Status;

typedef struct Items {
        char *bomb;
        char *potion;
        char *cure;
        char *book;
        char *shield;
        char *cannon;
}       Items;

int main(int argc, char *argv[]) {
        struct User_Status U;                                                   //User_Status 구조체 선언

        FILE *fp = fopen("test_sample.txt ", "rb");                             //바이너리 모드 읽기 전용으로 파일 열기

        fscanf(fp, "%s, %s, %s, %s, %s, %s, %hd", U.id, U.name, U.gender, U.age, U.HP, U.MP, U.coin);   //파일에서 읽어오기
        fclose(fp);                                                                                                                  //파일 닫기

        printf("*USER STATUS*\n");

        printf("ID : %s\n NAME : %s\n GENDER : %s\n AGE : %s\n HP : %s\n MP : %s\n COIN : %s\n");                                    //User_Status 출력

        struct Items I;                                                                 //Items 구조체 선언

        fp = fopen("test_sample.txt ", "rb");                           //바이너리 모드 읽기 전용으로 파일 열기

        fscanf(fp, "%s, %s, %s, %s, %s, %s", I.bomb, I.potion, I.cure, I.book, I.shield, I.cannon);
                                                                                                                                     //파일에서 읽어오기
        fclose(fp);                                                                                                                  //파일 닫기

        printf("*ITEMS*\n");

        printf("BOMB : %s\n     POTION : %s\n CURE : %s\n BOOK : %s\n SHIELD : %s\n CANNON : %s\n");                                 //ITEMS 출력

        //Friend_List
        printf("*FRIENDS LIST*\n");

        fp = fopen("test_sample.txt ", "rb");       //바이너리 모드 읽기 전용으로 파일 열기

        fread(&User_Status, sizeof(User_Status), 1, fp);

        for(int i = 1; i < 4; i++) {
                printf("Friend%d ID : %s\n Friend%d NAME : %s\n Friend%d GENDER : %s\n Friend%d AGE : %s\n", i, U.id, i, U.name, i, U.gender, i, U.age);
        }

        fclose(fp);

        //DESCRIPTION
        int num;
        char str[10000];

        printf("*DESCRIPTION*\n");

        fp = fopen("test_sample.txt ", "rb");       //바이너리 모드 읽기 전용으로 파일 열기i

        while(fp == 0) {
                num = fread(str, sizeof(int), 1, fp);
                printf("%s", str);
        }

        printf("\n");

        fclose(fp);

        return 0;

}

