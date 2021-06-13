#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 255

void input_id () { //이용자로부터 정보를 입력받는 함수
	int age, HP;
	double coorx, coory;
	char ally[MAX_SIZE][MAX_SIZE];
	int ally_count, ally_size;
	char ID[MAX_SIZE], order;
	int ID_size, i = 0;
	int loop = 1;
	
	FILE *fp = fopen("user.bin", "wb"); //binary 쓰기모드로 bin파일을 연다.
	if(fp == NULL) {
		fprintf(stderr, "Can't Open the File!\n");
		exit(1);
	}

	while(loop) { //이용자로부터 ID를 입력받는다. 단, 조건을 만족할 때 까지 반복한다.
		printf("ID를 입력하세요: ");
		scanf(" %s", ID);
		if(strlen(ID) > MAX_SIZE) printf("ID길이를 초과했습니다!\n"); //ID길이 255초과하면 다시 ID를 묻는다.
		else loop = 0; //ID길이가 255자 이하면 통과
	}loop = 1; //다음 loop사용을 위해 loop을 다시 1로 초기화
	ID_size = strlen(ID); //strlen함수를 이용해서 ID길이를 구해 int형 ID_size에 저장
	fwrite(&ID_size, sizeof(int), 1, fp); //파일에 ID를 기록하기 전 ID를 읽을때를 위해 길이를 저장
	fwrite(ID, strlen(ID), 1, fp); //ID를 그 뒤에 저장한다.

	printf("나이를 입력하세요: ");
	scanf(" %d", &age);
	fwrite(&age, sizeof(int), 1, fp);
	
	printf("HP를 입력하세요: ");
	scanf(" %d", &HP);
	fwrite(&HP, sizeof(int), 1, fp);

	printf("X좌표를 입력하세요: ");
	scanf(" %lf", &coorx);
	fwrite(&coorx, sizeof(double), 1, fp);

	printf("Y좌표를 입력하세요: ");
	scanf(" %lf", &coory);
	fwrite(&coory, sizeof(double), 1, fp);

	while(loop) { //이용자가 더 입력받지 않는다고 하거나 255개를 넘어갈 때 까지 동맹ID 입력받는다.
		while(loop) { //조건을 만족할때 까지 동맹ID를 입력받는다.
			printf("동맹 ID를 입력하세요: ");
			scanf(" %s", ally[i]);
			if(strlen(ally[i]) > MAX_SIZE) printf("ID길이를 초과했습니다!\n"); //ID길이 255초과 불가
			else { //ID길이가 정상이라면 while loop 탈출
				loop = 0;
				i++;
			}
		}loop = 1;
		ally_count++; //동맹ID갯수 +1카운트
		if(i >= MAX_SIZE) { //동맹 255개 이상 입력불가
			printf("더 이상 입력할 수 없습니다!");
			loop = 0;
		}
		printf("동맹을 계속 추가할까요?: "); //이용자가 N입력하면 더이상 입력받지 않는다.
		scanf(" %c", &order);
		if(order == 'N') loop = 0;
	}
	fwrite(&ally_count, sizeof(int), 1, fp); //동맹 ID 입력 전 총 ID 총 갯수를 파일에 저장
	
	for(int k = 0; k < ally_count; k++) {
		ally_size = strlen(ally[k]); //매번 기록 시 마다 문자열의 길이를 구해 파일에 저장
		fwrite(&ally_size, sizeof(int), 1, fp);
		fwrite(ally[k], ally_size, 1, fp);
	}
	printf("완료되었습니다.\n\n");	
	fclose(fp);
}

void output_id() { //기록된 정보를 출력하는 함수
	int age, HP;
	double coorx, coory;
	char ally[MAX_SIZE][MAX_SIZE];
	int ally_count, ally_size;
	char ID[MAX_SIZE];
	int ID_size;

	FILE *fp = fopen("user.bin", "rb"); //binary읽기 모드로 파일을 연다.
	if(fp == NULL) {
		fprintf(stderr, "Can't Open the File!\n");
		exit(1);
	}
	
	fread(&ID_size, sizeof(int), 1, fp); //ID앞에 size를 읽어 size길이 만큼 ID를 읽어온다.
	fread(ID, ID_size, 1, fp);
	fread(&age, sizeof(int), 1, fp);
	fread(&HP, sizeof(int), 1, fp);
	fread(&coorx, sizeof(double), 1, fp);
	fread(&coory, sizeof(double), 1, fp);
	fread(&ally_count, sizeof(int), 1, fp);

	printf("ID: %s / 나이: %d / HP: %d / 좌표: %.3f, %.3f\n", ID, age, HP, coorx, coory);
	printf("등록된 동맹 수: %d명\n", ally_count);
	for(int k = 0; k < ally_count; k++) {
		fread(&ally_size, sizeof(int), 1, fp); //매번 read마다 동맹ID 파일길이를 읽어 그 길이만큼의 문자열 받기
		fread(ally[k], ally_size, 1, fp);
		printf("%s", ally[k]);
		if(k != ally_count -1) printf(" / "); //마지막 동맹ID 출력 전까지 ' / ' 출력한다.
	}
	printf("\n완료되었습니다.\n\n");
	fclose(fp);
}

void PrintMenu() {
	printf("1. 플레이어 정보 기록\n2. 플레이어 정보 확인\n3. 종료\n");
	printf("입력하세요> ");
}

int main() {
	int order = 0, loop = 1;

	while(loop) {
		PrintMenu();
		scanf(" %d", &order);
		switch (order) {
			case 1: input_id(); break;
			case 2: output_id(); break;
			case 3: printf("종료되었습니다.\n\n"); loop = 0; break;
		}
	}
	return 0;
}
