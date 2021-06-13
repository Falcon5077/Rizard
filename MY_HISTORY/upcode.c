#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void checkout_buff(unsigned char *buff, unsigned char *script) { //파일로 부터 받아온 Description을 확인한다.
	int len = 0, count = 0;	//len: 각 위치의 문자열 길이를 읽어서 저장시키는 변수, count: 문자열 한 줄에서 바뀌는 문자시작점~ 끝점까지의 길이 할당받는다.
	int start; //문자가 바뀌는 위치의 위치값 저장
	unsigned char strA;
	int x = 0;

	len = strlen(script);
	for(int k = 0; k <= len; k++) {	//len 길이만큼 반복(한줄)
		if(count == 0) {
			strA = script[k]; //반복 중 다른 문자가 시작하는 첫지점이면 그 지점의 값을 strA에 저
			start = k;
		}
		count++;
		if(strA != script[k]) {
			if(strA > 47 && strA < 58) { //입력된 값이 숫자인경우
				if(count - 1 == 1) { //숫자가 한개만 있을때 
					for(int z = 0; z < 3; z++)
						buff[x++] = strA - 20; //ASCII 값에서 20빼서 저장 3번
				}
				if(count - 1 == 2) { //반복되는 숫자가 두개있을 경우
					for(int z = 0; z < 3; z++) //ASCII값에서 10빼서 저장 3번
						buff[x++] = strA - 10;
				}
				if(count - 1 >= 3) { //반복되는 숫자가 세개 이상일 경우
					for(int z = 0; z < 3; z++) //숫자 ASCII값에서 10뺀거 3번 + 반복되는 횟수 3번 저장
						buff[x++] = strA - 10;
					for(int z = 0; z < 3; z++)
						buff[x++] = count-1;
				}
			}else {		//숫자가 아니라 문자인 경우
				if((count-1) >= 3) { //같은 문자가 3개이상인 경우
					for(int z = 0; z < 3; z++)	//3번 입력
						buff[x++] = strA + 32;	//아스키값 +32해서 소문자로 변경
					for(int z = 0; z < 3; z++)
						buff[x++] = count-1;		//count는 현재 갯수보다 1크므로 -1해서 대입
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
}


void insert_file(unsigned char *buff) { //파일.... 넣을게...
	FILE *fp = fopen("encode.bin", "wb");
	if(fp == NULL) {
		fprintf(stderr, "Can't Open the File!\n");
		exit(1);
	}
	fwrite(buff, strlen(buff), 1, fp); //3번씩 저장한 최종버퍼를 encode.bin파일에 넣을게...

	fclose(fp);
}

int main(int argv, char *argc[]) {
	unsigned char script[100] = "BBB222"; //이게 테스팅용으로 들어가는 값임 (원본값을 여기다 대입하면 되용)
	unsigned char buff[3000]; //원본값을 변환시킨 값이 들어가는 버퍼(일단 세번씩 반복하는거니 최악의 경우를 대비해서 크기 3000잡아놈

	checkout_buff(buff, script);
	insert_file(buff);

	return 0;
}
