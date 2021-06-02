#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void checkout_buff(unsigned char *buff, unsigned char *script) { //파일로 부터 받아온 Description을 확인해서 1개짜리로 바꿔 buff에 저장한다.(1차 변형)
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
				if(count - 1 == 1) buff[x++] = strA - 20; //같은 갯수가 1개인경우 ASCII 값에서 20빼기
				if(count - 1 == 2) buff[x++] = strA - 10; //같은 갯수가 2개인경우 ASCII값에서 10빼기
				if(count - 1 >= 3) { //반복되는 숫자가 세개 이상일 경우
					buff[x++] = strA - 10; //ASCII값 10빼고 갯수 저장
					if(count - 1 == 10) buff[x++] = 126;
					else buff[x++] = count-1;
				}
			}else {		//숫자가 아니라 문자인 경우
					if(count - 1 >= 3) { 	//같은 문자가 3개이상인 경우
							buff[x++] = strA + 32;		//아스키값 +32해서 소문자로 변경
							if(count - 1 == 10) buff[x++] = 126;
							else buff[x++] = count - 1;		//count는 현재 갯수보다 1크므로 -1해서 대입
					}
					if(count - 1 == 2) buff[x++] = strA + 32; //같은 문자가 두개인 경우 소문자 한개 저장
					if(count - 1 == 1) buff[x++] = strA; //같은 문자가 하나인 경우 그대로 저장
					}
				count = 0;
				k--;
			}
		}
	buff[x++] = '\n';
	buff[x++] = '\0';
}

void checkout_same_line(unsigned char *buff) {
	unsigned char temp[1000][1000];
	unsigned char temp2[1000];
	int x = 0, height = 5;
	int len = strlen(buff);

	for(int i = 0; i < height; i++) { //for문이 두번 딱 돌면서 2차원 배열로 바꿔준다~ 이말이야
		for(int k = 0; k < len; k++) { //반복하면서 \n나올때 까지 temp2에 값을 저장
			temp2[k] = buff[x];	
			if(buff[x] == '\n') { //temp2 x번째에 \n이 들어갔다.
				temp2[++k] = '\0'; //temp2마지막 위치에 null포인터 저장
				break; //안쪽 for문 탈출
			}
			x++; //개행문자가 없으면 위의 if문은 그냥 지나쳐오고 buff다음위치 값을 temp에 대입하기 위해 x++해준다
		}
		strcpy(temp[i], temp2); //break한 이후 temp[i]에 temp2의 값을 복사한다.
	}

	for(int i = 0; i < 5; i++) //출력해서 temp에 제대로 들어갔는지 확인
		printf("%s", temp[i]);

	for(int i = 0; i < height; i++) { //반복문이 돌면서 i번째 temp값과 그보다 1큰 k값으로 두 값을 비교한다.
		for(int k = i+1; k < height; k++) {
			if(strcmp(temp[i], temp[k]) == 0){ //두 값이 같으면
				strcpy(temp[k], "="); //k번째 temp에 =+같은 줄번호\n\0을 입력한다.
				temp[k][1] = i+1;
				temp[k][2] = '\n';
				temp[k][3] = '\0';
			}
		}
	}
	x = 0; 
	for(int i = 0; i < height; i++) { //완성된 값을 for문이 돌면서 순서대로 값을 buff에 입력한다.
		for(int k = 0; temp[i][k] != '\0'; k++)
			for(int j = 0; j < 3; j++)
				buff[x++] = temp[i][k];
	}
	buff[x++] = '\0';
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
	unsigned char script[1000] = "ABCDE\nABCDE\nABCDE\n33333AAAAA\nJEON"; //이게 테스팅용으로 들어가는 값임 (원본값을 여기다 대입하면 되용)
	unsigned char buff[3000]; //원본값을 변환시킨 값이 들어가는 버퍼(일단 세번씩 반복하는거니 최악의 경우를 대비해서 크기 3000잡아놈

	checkout_buff(buff, script);
	checkout_same_line(buff);
	insert_file(buff);

	return 0;
}
