//이준우
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

//User_Status
unsigned char id;
unsigned char *name;
unsigned char gender;
char *age;
char HP;
char MP;
unsigned short coin;

//Items
char bomb;
char potion;
char cure;
char book;
char shield;
char cannon;

char description[1000];

void DownLoad() {                                                                       //txt파일에서 구조체로 끌어오는 함수
        FILE *fp1 = fopen("test_sample1.txt", "rb");            //바이너리 쓰기 전용 모드로 파일 열기
        FILE *fp2 = fopen("test_sample2.txt", "rb");            //바이너리 쓰기 전용 모드로 파일 열기

        if(fp1 == NULL) {
                fprintf(stderr, "Error...\n");
                exit(1);
        }

        if(fp2 == NULL) {
                fprintf(stderr, "Error...\n");
                exit(1);
        }

        //파일에서 읽기
        fread(&id, sizeof(unsigned char), 1, fp1);
        fread(&id, sizeof(unsigned char), 1, fp2);

        fread(name, sizeof(unsigned char), 1, fp1);
        fread(name, sizeof(unsigned char), 1, fp2);

        fread(&gender, sizeof(unsigned char), 1, fp1);
        fread(&gender, sizeof(unsigned char), 1, fp2);

        fread(age, sizeof(char), 1, fp1);
        fread(age, sizeof(char), 1, fp2);

        fread(&HP, sizeof(char), 1, fp1);
        fread(&HP, sizeof(char), 1, fp2);

        fread(&MP, sizeof(char), 1, fp1);
        fread(&MP, sizeof(char), 1, fp2);

        fread(&coin, sizeof(char), 1, fp1);
        fread(&coin, sizeof(char), 1, fp2);

        fread(&bomb, sizeof(char), 1, fp1);
        fread(&bomb, sizeof(char), 1, fp2);

        fread(&potion, sizeof(char), 1, fp1);
        fread(&potion, sizeof(char), 1, fp2);

        fread(&cure, sizeof(char), 1, fp1);
        fread(&cure, sizeof(char), 1, fp2);

        fread(&book, sizeof(char), 1, fp1);
        fread(&book, sizeof(char), 1, fp2);

        fread(&shield, sizeof(char), 1, fp1);
        fread(&shield, sizeof(char), 1, fp2);

        fread(&cannon, sizeof(char), 1, fp1);
        fread(&cannon, sizeof(char), 1, fp2);

        fclose(fp1);
        fclose(fp2);

        //파일에 작성
        fp1 = fopen("test_sample1.txt", "wb");          //바이너리 쓰기 전용 모드로 파일 열기
        fp2 = fopen("test_sample2.txt", "wb");          //바이너리 쓰기 전용 모드로 파일 열기

        fwrite(&id, sizeof(unsigned char), 3, fp1);
        fwrite(&id, sizeof(unsigned char), 3, fp2);

        fwrite(name, sizeof(unsigned char), 3, fp1);
        fwrite(name, sizeof(unsigned char), 3, fp2);

        fwrite(&gender, sizeof(unsigned char), 3, fp1);
        fwrite(&gender, sizeof(unsigned char), 3, fp2);

        fwrite(age, sizeof(char), 3, fp1);
        fwrite(age, sizeof(char), 3, fp2);

        fwrite(&HP, sizeof(char), 3, fp1);
        fwrite(&HP, sizeof(char), 3, fp2);

        fwrite(&MP, sizeof(char), 3, fp1);
        fwrite(&MP, sizeof(char), 3, fp2);

        fwrite(&coin, sizeof(char), 3, fp1);
        fwrite(&coin, sizeof(char), 3, fp2);

        fwrite(&bomb, sizeof(char), 3, fp1);
        fwrite(&bomb, sizeof(char), 3, fp2);

        fwrite(&potion, sizeof(char), 3, fp1);
        fwrite(&potion, sizeof(char), 3, fp2);

        fwrite(&cure, sizeof(char), 3, fp1);
        fwrite(&cure, sizeof(char), 3, fp2);

        fwrite(&book, sizeof(char), 3, fp1);
        fwrite(&book, sizeof(char), 3, fp2);

        fwrite(&shield, sizeof(char), 3, fp1);
        fwrite(&shield, sizeof(char), 3, fp2);

        fwrite(&cannon, sizeof(char), 3, fp1);
        fwrite(&cannon, sizeof(char), 3, fp2);

        fclose(fp1);
        fclose(fp2);
}

int main(int argc, char *argv[]) {
        DownLoad();

        return 0;
}

