#include <stdio.h>
#include <string.h>
typedef struct {
	char ID[255];
	char name[255];
	char gender;
	char age;
}info; // 동맹 구조체

info FRIEND[100];
int num = 0; // 동맹수

void READ() {
	FILE *fp = fopen("project.bin","rb"); // 오류가 난 파일 열기
	char buffer[1000] = {0,}; // bin에서 받는 ID정보 저장용
	char buffer_n[1000] = {0,}; // bin에서 받는 name정보 저장용
	char buffer_g[3] = {0,}; // bin에서 받는 gender정보 저장용
	char buffer_age[3];
	char compare[3]; // 비교변수
	int index = 0; // 인덱스 위치에 compare끼리 비교후 넣어 줄 위치

	// ID 정보 입력
	fread(buffer, sizeof(char),21,fp); // 파일 읽고
	for(int i = 0; buffer[i] != 0; i = i + 3) { //ex KK9
		compare[0] = buffer[i]; //K
		compare[1] = buffer[i+1]; //K
		compare[2] = buffer[i+2]; //9
		
		if(compare[0]==compare[1]) {
			FRIEND[0].ID[index] = compare[0];
			index++;
		} // K == K 이므로 FRIEND[0].ID[index] 위치에 넣어주고 index++
		
		else if(compare[0]==compare[2]) {
			FRIEND[0].ID[index] = compare[0];
			index++;
		}

		else {
			FRIEND[0].ID[index] = compare[1];
			index++;
		}
	} // 어디가 바뀌었는지 확인하자!

	// name 정보 입력
	index = 0;
	fread(buffer_n, sizeof(char), 15, fp);
	for(int i = 0; buffer_n[i] != 0; i = i+3) { //ID 정보와 설명같음
		compare[0] = buffer_n[i];
		compare[1] = buffer_n[i+1];
		compare[2] = buffer_n[i+2];

		if(compare[0]==compare[1]) {
			FRIEND[0].name[index] = compare[0];
			index++;
		}

		else if(compare[0]==compare[2]) {
			FRIEND[0].name[index] = compare[0];
			index++;
		}
		
		else {
			FRIEND[0].name[index] = compare[1];
			index++;
		}
	}

	fread(buffer_g, sizeof(char), 3, fp); // ex) M!M
	if(buffer_g[0]==buffer_g[1]) { // M은 !와 다르므로 if문 통과
		FRIEND[0].gender = buffer_g[0]; 
	}

	else if(buffer_g[0]==buffer_g[2]) { //M과 M을 비교해서 같으므로
		FRIEND[0].gender = buffer_g[0];
	} // gender는 M이다.

	else {
		FRIEND[0].gender = buffer_g[1];
	}

	// 나이 정보 저장
	fread(buffer_age, sizeof(char), 3 ,fp); 
	if(buffer_age[0]==buffer_age[1]) { // 성별 설명과 같다.
		FRIEND[0].age = buffer_age[0];
	}

	else if(buffer_age[0]==buffer_age[2]) {
		FRIEND[0].age = buffer_age[0];
	}

	else {
		FRIEND[0].age = buffer_age[1];
	}
}

void print() { // 정보출력
	printf("ID : %s\n",FRIEND[0].ID);
	printf("NAME : %s\n",FRIEND[0].name);
	if(FRIEND[0].gender == 'M') {
		printf("GENDER : MALE\n");
	}
	else {
		printf("GENDER : FEMALE\n");
	}
	printf("AGE : %hd\n",FRIEND[0].age);
}

int main() {
	READ();
	print();	
	return 0;
}
