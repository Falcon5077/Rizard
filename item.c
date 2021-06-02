#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

FILE* fp1;
FILE* fp2;

char tmp_Items[255] = { 0 }; // 텍스트파일의 아이템 상황을 저장하는 문자열
						   // 아이템 존재하면 이름, 없으면 0 대입
unsigned char* Check_Item(void);
void Whrite_Item(unsigned char*);

int main() {//int argc, char* argv[]) {
	/*if (argc != 2) {
		printf("Error!\n");
		exit(1);
	}*/
	//f1name = argv[1];
	//f2name = argv[2];
	fp1 = fopen("test_sample.txt", "r+t");
	fp2 = fopen("my.bin", "wb");

	// 아이템 배열에서 끌고와서 저장하는 함수
	unsigned char* item_count = Check_Item();
	// 저장한 값으로 아이템 정보 인코딩하는 함수
	Whrite_Item(item_count);

	fclose(fp1);
	fclose(fp2);
	return 0;
}


unsigned char* Check_Item(void) {
	char buf[1000];
	char* line; // fgets로 끌고와서 저장하는 문자열(한줄 전체)
	char* tmp;	// 텍스트파일에 존재하는 아이템이름 저장하는 문자열(아이템 이름)
	char* ptr;  // 아이템 개수 저장하는 문자열

	int index = 0; // 몇번째 필드인지 구분
	int count = 0; // 몇번째 아이템인지 구분하는 변수
	unsigned char tmp_item_count[6] = {0}; // 아이템별 개수 저장하는 배열
		
	while (!feof(fp1)) {
		line = fgets(buf, sizeof(buf), fp1);
		if (line == NULL)
			break;

		index = 2; // 임시로 아이템만 읽게끔 설정

		if (strstr(line, "*")) {	// 필드구분                                                       //필드 검사 if문
			printf("%d 번째 필드\n", index);
			continue;
		}

		
		if (index == 2) {
			tmp = strtok(line, " ");
			if (tmp != NULL) {
				tmp[strlen(tmp) - 1] = '\0';
				//  tmp_Items에 텍스트파일 순서로 아이템 이어 붙이기
				strcat(tmp_Items, tmp);
				strcat(tmp_Items, "/"); // /로 아이템 구분
				
				ptr = strtok(NULL, "\n"); // \n으로 문자열 잘라서 개수 찾기

				if (atoi(ptr) != 0) // 개수를 정수화
					tmp_item_count[count] = atoi(ptr); // 정수형 배열에 대입

				else if (atoi(ptr) == 0)
					tmp_item_count[count] = 0;	//	아이템별 개수 없으면 0
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
			strcat(tmp_Items, "0/");		  // 0으로 저장
			tmp_item_count[count + i] = 0;    // 개수 저장 배열에도 0 대입
		}
	}

	if (tmp_Items[strlen(tmp_Items) - 1] == '/')
		tmp_Items[strlen(tmp_Items) - 1] = '\0';

	return tmp_item_count; // 개수 저장 배열 리턴

	/*for (int i = 0; i < 6; i++) {
		printf("%s : %d\n", tmp_Items, tmp_item_count[i]);
	}*/
		
}

void Whrite_Item(unsigned char* item_count) {
	char* str; // 자른 문자열 저장하는 함수
	int i, num; 
	int tmp_count = 0; // ptr과 Items[i]와 같을때의 i값 
	char sort = 0;

	str = strtok(tmp_Items, "/");
	while (str != NULL) {
		str = strtok(NULL, "/"); // 슬래쉬(/) 단위로 자르기
		for (int i = tmp_count; i < 6; i++) {
			if ((num = strcmp(Items[i], str)) == 0) {
				tmp_count = i;
				break;
			}
			else if (num != 0) {
				return sort
			}
		}
		
	}

}
