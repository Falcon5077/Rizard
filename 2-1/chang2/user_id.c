#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 255

void input_id () {
	int age, HP;
	double coorx, coory;
	char ally[MAX_SIZE][MAX_SIZE];
	int ally_count, ally_size;
	char ID[MAX_SIZE], order;
	int ID_size, i = 0;
	int loop = 1;
	
	FILE *fp = fopen("user.bin", "wb");
	if(fp == NULL) {
		fprintf(stderr, "Can't Open the File!\n");
		exit(1);
	}

	while(loop) {
		printf("ID를 입력하세요: ");
		scanf(" %s", ID);
		if(strlen(ID) > 255) printf("ID길이를 초과했습니다!\n"); //ID길이 255초과금지
		else loop = 0;
	}loop = 1;
	ID_size = strlen(ID);
	fwrite(&ID_size, sizeof(int), 1, fp);
	fwrite(ID, strlen(ID), 1, fp);

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

	while(loop) {
		while(loop) {
			printf("동맹 ID를 입력하세요: ");
			scanf(" %s", ally[i]);
			if(strlen(ally[i]) > 255) printf("ID길이를 초과했습니다!\n"); //ID길이 255초과 불가
			else {
				loop = 0;
				i++;
			}
		}loop = 1;
		ally_count++;
		if(i >= 255) { //동맹 255개 이상 입력불가
			printf("더 이상 입력할 수 없습니다!");
			loop = 0;
		}
		printf("동맹을 계속 추가할까요?: ");
		scanf(" %c", &order);
		if(order == 'N') loop = 0;
	}
	ally_size = strlen(ally[0]);
	fwrite(&ally_count, sizeof(int), 1, fp);
	fwrite(&ally_size, sizeof(int), 1, fp);
	
	for(int k = 0; k < ally_count; k++)
		fwrite(ally[k], ally_size, 1, fp);
	printf("완료되었습니다.\n\n");	
	fclose(fp);
}

void output_id() {
	int age, HP;
	double coorx, coory;
	char ally[MAX_SIZE][MAX_SIZE];
	int ally_count, ally_size;
	char ID[MAX_SIZE];
	int ID_size;

	FILE *fp = fopen("user.bin", "rb");
	if(fp == NULL) {
		fprintf(stderr, "Can't Open the File!\n");
		exit(1);
	}
	
	fread(&ID_size, sizeof(int), 1, fp);
	fread(ID, ID_size, 1, fp);
	fread(&age, sizeof(int), 1, fp);
	fread(&HP, sizeof(int), 1, fp);
	fread(&coorx, sizeof(double), 1, fp);
	fread(&coory, sizeof(double), 1, fp);
	fread(&ally_count, sizeof(int), 1, fp);
	fread(&ally_size, sizeof(int), 1, fp);

	printf("ID: %s / 나이: %d / HP: %d / 좌표: %.3f, %.3f\n", ID, age, HP, coorx, coory);
	printf("등록된 동맹 수: %d명\n", ally_count);
	for(int k = 0; k < ally_count; k++) {
		fread(ally[k], ally_size, 1, fp);
		printf("%s", ally[k]);
		if(k != ally_count -1) printf(" / ");
	}
	printf("\n완료되었습니다.\n\n");
	fclose(fp);
}

void PrintMenu() {
	printf("1. 플레이어 정보 기록\n2. 플레이어 정보 확인\n3.종료\n");
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
			case 3: loop = 0;
		}
	}
	return 0;
}
