#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//char* f1name;
//char* f2name;

char* Items[] = {
   "BOMB",
   "POTION",
   "CURE",
   "BOOK",
   "SHIELD",
   "CANNON"
};

// 전역변수 
FILE* fp1;
FILE* fp2;
char* str; // 자른 문자열 저장하는 함수
char count = 0; // 몇번째 아이템인지 구분하는 변수
unsigned char tmp_item_count[6] = { 0 }; // 아이템별 개수 저장하는 배열
char tmp_Items_list[255] = { 0 }; // 텍스트파일의 아이템 상황을 저장하는 문자열
char Items_list[255] = { 0 }; // 아이템 존재하면 이름, 없으면 0 대입
// 함수 선언
void Check_Item(void);
char Check_Item_sort();
void Write_Item(char);
void WriteChar(unsigned char);

int main() {//int argc, char* argv[]) {
   /*if (argc != 2) {
      printf("Error!\n");
      exit(1);
   }*/
   //f1name = argv[1];
   //f2name = argv[2];
    fp1 = fopen("test_sample.txt", "r+t");
    fp2 = fopen("godd.bin", "wb");
    char sort;
    
    // 아이템 배열에서 끌고와서 저장하는 함수
    Check_Item();
    strcpy(Items_list, tmp_Items_list);
    // 저장한 값으로 아이템의 순서규칙 확인하는 함수
    // sort 값이 1이면 순서대로, 0이면 순서대로x
    sort = Check_Item_sort();

    for (int i = 0; i < count; i++) {
        printf("%d ",tmp_item_count[i]);
    }
    
    Write_Item(sort);

    fclose(fp1);
    fclose(fp2);
    return 0;
}

void Check_Item(void) {
    char buf[1000];
    char* line; // fgets로 끌고와서 저장하는 문자열(한줄 전체)
    char* tmp;   // 텍스트파일에 존재하는 아이템이름 저장하는 문자열(아이템 이름)
    char* ptr;  // 아이템 개수 저장하는 문자열

    int index = 0; // 몇번째 필드인지 구분
    
    while (!feof(fp1)) {
        line = fgets(buf, sizeof(buf), fp1);
        if (line == NULL)
            break;

        index = 2; // 임시로 아이템만 읽게끔 설정

        if (strstr(line, "*")) {   // 필드구분                                                       //필드 검사 if문
            printf("%d 번째 필드\n", index);
            continue;
        }


        if (index == 2) {
            tmp = strtok(line, " ");
            if (tmp != NULL) {
                tmp[strlen(tmp) - 1] = '\0';
                //  tmp_Items에 텍스트파일 순서로 아이템 이어 붙이기
                strcat(tmp_Items_list, tmp);
                strcat(tmp_Items_list, "/"); // /로 아이템 구분

                ptr = strtok(NULL, "\n"); // \n으로 문자열 잘라서 개수 찾기

                if (atoi(ptr) != 0) // 개수를 정수화
                    tmp_item_count[count] = (unsigned char)atoi(ptr); // 정수형 배열에 대입

                else if (atoi(ptr) == 0)
                    tmp_item_count[count] = 0;   //   아이템별 개수 없으면 0
            }

            if (count != 6) {
                count++; // 아이템 총 개수 계산
                continue;
            }
            else
                break;
        }
    }

    if (count != 6) {
        for (int i = 0; i < 6 - count; i++) { // 없는 아이템은 tmp_Items에
            strcat(tmp_Items_list, "0/");        // 0으로 저장
            tmp_item_count[count + i] = 0;    // 개수 저장 배열에도 0 대입
        }
    }

    if (tmp_Items_list[strlen(tmp_Items_list) - 1] == '/')
        tmp_Items_list[strlen(tmp_Items_list) - 1] = '\0';

    //return tmp_item_count; // 개수 저장 배열 리턴

    /*for (int i = 0; i < 6; i++) {
       printf("%s : %d\n", tmp_Items, tmp_item_count[i]);
    }*/

}

char Check_Item_sort(void) {
    int i, num;
    char tmp_count[6] = {0}; // ptr과 Items[i]와 같을때의 i값
    int for_count = 0; // for문 돌아가는 횟수
    char sort = 0;

    str = strtok(tmp_Items_list, "/"); // 슬래쉬(/) 단위로 잘라서 str에 저장
    while (str != NULL) { // 자른 값이 NULL이 아닐때 
        for (i = 0; i < 6; i++) { 
            if ((num = strcmp(Items[i], str)) == 0) { // str값이 Items[i] 랑 같을 때
                tmp_count[for_count++] = i;           // tmp_count에 i값 저장
                if (for_count >= 2) {                 // 비교할 값이 2개이상일때만 작동
                    for (int j = 0; j < for_count - 1; j++) { 
                        if (tmp_count[j] > tmp_count[j + 1]) // tmp_count에 저장된 값이 순서대로가 아닐때
                            return sort;  // sort 값 0으로 반환
                        else
                            continue;
                    }
                }
                else
                    break;
            }
            else if (num != 0)
                continue;
        }
        str = strtok(NULL, "/"); // 슬래쉬(/) 단위로 자르기
    }
    if (sort == 0)
        return ++sort; // 순서대로라는 뜻으로 0값 반환
}

void Write_Item(char sort) {
    int num, tmp_count = 0, result;
    unsigned binary_result = 0;
    char binary[6] = { 0 };
    if (sort == 1) {
        WriteChar(count); // 총 개수 파일에 쓰기

        str = strtok(Items_list, "/");
        while (str != NULL) {
            if ((num = strcmp(Items[tmp_count], str)) == 0)
                binary[tmp_count++] = 1;

            else if (num != 0)
                binary[tmp_count++] = 0;

            str = strtok(NULL, "/");
        }

        for (int i = 5; i > 0; i--) {
            result = pow(2, i);
            binary_result += (unsigned char)result * binary[5 - i];
        }
        if (1 <= count && count <= 4) {
            WriteChar(binary_result);
            for (int i = 0; i < count; i++)
                WriteChar(tmp_item_count[i]);
        }
        else if (5 <= count && count <= 6) {

        }
    }

    else if (sort == 0) {
        WriteChar(sort); // sort값 파일에 쓰기
        WriteChar(count);// 총 개수 파일에 쓰기
        // BOMB/CANNON~~~
        str = strtok(Items_list, "/");
        while (str != NULL) {
            for (int i = 0; i < 6; i++) {
                if ((num = strcmp(Items[i], str)) == 0) {
                    WriteChar(i);
                    WriteChar(tmp_item_count[tmp_count++]);
                    break;
                }
                else if (num != 0)
                    continue;
            }     
            str = strtok(NULL, "/");
        }

    }
}

void WriteChar(unsigned char len)
{
    for (int i = 0; i < 3; i++)
        fwrite(&len, 1, sizeof(unsigned char), fp2);
}

