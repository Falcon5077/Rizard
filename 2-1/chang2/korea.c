#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_info() {
	char ident[255];
	char order;
	int age, health;
	int t = 0, count=0;
	double x, y;
	char ally[255][255];
	int id_size, ally_size;

	FILE *fp = fopen("User.bin", "wb");
	if(fp == NULL) {
		fprintf(stderr, "Can't open file!\n");
		exit(1);
	}

	printf("ID를 입력하세요: ");
	scanf(" %s", ident);
	
	printf("나이를 입력하세요: ");
	scanf(" %d", &age);

	printf("HP를 입력하세요: ");
	scanf(" %d", &health);

	printf("X좌표를 입력하세요: ");
	scanf(" %lf", &x);
	printf("Y좌표를 입력하세요: ");
	scanf(" %lf", &y);

	for(int i = 0; t != 1; i++) {
		if(i == 254) { 
			printf("더이상 입력 할 수 없습니다!\n");
			break;
		}
		count++;
		printf("동맹 ID를 입력하세요: ");
		scanf(" %s", ally[i]);
		printf("동맹을 계속 추가할까요?: ");
		scanf(" %c", &order);
		if(order == 'N') t = 1;
	}
	id_size = strlen(ident);
	ally_size = strlen(ally[0]);
	fwrite(&id_size, sizeof(int), 1, fp);
	fwrite(ident, strlen(ident), 1, fp);
	fwrite(&age, sizeof(int), 1, fp);
	fwrite(&x, sizeof(double), 1, fp);
	fwrite(&y, sizeof(double), 1, fp);

	fwrite(&ally_size, sizeof(int), 1, fp);
	fwrite(&count, sizeof(int), 1, fp);
	for(int i = 0; i < count; i++)
		fwrite(ally[i], strlen(ally[i]), 1, fp);
	fclose(fp);
}

void read_info() {
	char ident[255];
	int age, health, count;
	double x, y;
	char ally[255][255];
	int size_id = 0, size_ally = 0;

	FILE *fp = fopen("User.bin", "r+b");
	if(fp = NULL) {
		fprintf(stderr, "Can't open!\n");
		exit(1);
	}
	
	fread(&size_id, sizeof(int), 1, fp);
	printf("size_id: %d\n", size_id);
	fread(ident, size_id, 1, fp);
	printf("ID: %s / ", ident);
	fread(&age, sizeof(int), 1, fp);
	fread(&health, sizeof(int), 1, fp);
	fread(&x, sizeof(double), 1, fp);
	fread(&y, sizeof(double), 1, fp);
	fread(&size_ally, sizeof(int), 1, fp);
	fread(&count, sizeof(int), 1, fp);
	for(int i = 0; i < count; i++)
		fread(ally[i], size_ally, 1, fp);

	printf("ID: %s / 나이: %d / HP: %d / 좌표: %3.f, %3.f", ident, age, health, x, y);
	for(int i = 0; i < count; i++)
		printf("%s ", ally[i]);

	fclose(fp);
}

void PrintMenu() {
	printf("1. 플레이어 정보 기록\n2. 플레이어 정보 확인\n3. 종료\n입력하세요> ");
}

int main() {
	int order = 0, loop =1;
	
	while (loop) {
		PrintMenu();
		scanf("%d", &order);
		switch(order) {
			case 1: write_info(); break;
			case 2: read_info(); break;
			case 3: loop = 0; break;
			default: printf("Wrong order!"); break;
		}
	}
}
