#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void checkout_buff(char *buff, int height, char *script) { //파일로 부터 받아온 Description을 확인한다.
	int len = 0, count = 0;	//len: 각 위치의 문자열 길이를 읽어서 저장시키는 변수, count: 문자열 한 줄에서 바뀌는 문자시작점~ 끝점까지의 길이 할당받는다.
	int start; //문자가 바뀌는 위치의 위치값 저장
	char strA;
	int x = 0;

	len = strlen(script);
	for(int k = 0; k <= len; k++) {	//len 길이만큼 반복(한줄)
		if(count == 0) {
			strA = script[k]; //반복 중 다른 문자가 시작하는 첫지점이면 그 지점의 값을 strA에 저
			start = k;
		}
		count++;
		if(strA != script[k]) {
			if((count-1) >= 3) { //같은 문자가 3개이상인 경우
				for(int z = 0; z < 3; z++) {	//3번 입력
					buff[x++] = strA + 32;	//아스키값 +32해서 소문자로 변경
					buff[x++] = count-1;		//count는 현재 갯수보다 1크므로 -1해서 대입
				}
			}else {				//같은 문자가 2개이하인 경우
				for(int z = 0; z < 3; z++) { //3번입력
					for(int r = 0; r < count - 1; r++)
						buff[x++] = strA;
				}
			}
			count = 0;
			k--;
		}
	}
}


void insert_file(char *buff) {
	FILE *fp = fopen("encode.bin", "wb");
	if(fp == NULL) {
		fprintf(stderr, "Can't Open the File!\n");
		exit(1);
	}
	fwrite(buff, strlen(buff), 1, fp);

	fclose(fp);
}

int main(int argv, char *argc[]) {
	char script[40] = "AAAABCABCABC\nAFFCDAAABBC";
	char buff[1000];
	int height = 2;
	int len = 0;

	checkout_buff(buff, height, script);
	insert_file(buff);

	return 0;
}
