#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Save_Info(FILE *fp) {
	char name[255];
	char email[255];
	char ch;
	int age;

	fp = fopen("Info.txt", "a");

	if(fp == NULL) {
		fprintf(stderr, "파일을 열 수 없습니다.\n");
		return;
	} else {
		do{
			printf("이름: ");
			scanf(" %[^\n]s", name);
			
			printf("나이: ");
			scanf(" %d", &age);

			printf("이메일: ");
			scanf(" %s", email);
	
			fprintf(fp, "%s / %d / %s\n", name, age, email);
			printf("계속 입력 할까요?(Y/N) ");
			scanf(" %c", &ch);
		} while (ch != 'n');
		printf("입력이 완료되었습니다.\n\n");
		fclose(fp);
	}
}

void Del_Info(FILE *fp) {
	char *buf;
	char *p;
	char order[255];
	int size = 0, k = 1;

	printf("삭제할 사람 이름을 입력해주세요: ");
	scanf(" %[^\n]s", order);
	fp = fopen("Info.txt", "r+t");
	
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);

	buf = (char*)malloc(sizeof(char) * (size + 1));
	buf[size] = '\0';
	
	fseek(fp, 0, SEEK_SET);
	fread(buf, size, 1, fp);
	p = strstr(buf, order);

	if (p == NULL) {
		printf("사용자 %s는 없습니다.\n\n", order);
		free(buf);
		fclose(fp);
	}
	else {
		for(int i = 0; k != 0; i++) {
			if(p[i] == '\n') k = 0;
			p[i]  = '\b';
		}
		fseek(fp, 0, SEEK_SET);
		fprintf(fp, "%s", buf);
		printf("삭제가 완료되었습니다.\n\n");
		fclose(fp);
		free(buf);
	}
}

void Modify_Info(FILE *fp) {
	char *buf;
	char *p;
	char order[255], name[255], email[255];
	int size = 0, k = 1, age = 0;

	printf("수정할 사람 이름을 입력해주세요: ");
	scanf(" %[^\n]s", order);
	fp = fopen("Info.txt", "r+t");
	
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);

	buf = (char*)malloc(sizeof(char) * (size + 1));
	buf[size] = '\0';
	
	fseek(fp, 0, SEEK_SET);
	fread(buf, size, 1, fp);
	p = strstr(buf, order);

	if (p == NULL) {
		printf("사용자 %s는 없습니다.\n\n", order);
		free(buf);
		fclose(fp);
	}
	else {
		printf("사용자 %s 을 수정합니다.\n", order);
		for(int i = 0; k != 0; i++) {
			if(p[i] == '\n') k = 0;
			p[i]  = '\b';
		}
		fseek(fp, 0, SEEK_SET);
		fprintf(fp, "%s", buf);
		printf("이름: ");
		scanf(" %[^\n]s", name);
		
		printf("나이: ");
		scanf(" %d", &age);

		printf("이메일: ");
		scanf(" %s", email);

		fprintf(fp, "%s / %d / %s\n", name, age, email);
		printf("수정 완료 되었습니다.\n\n");
		fclose(fp);
		free(buf);
	}
}

void Print_List(FILE *fp) {
	char *buf;
	int size;

	fp = fopen("Info.txt", "r");
	
	fseek(fp, 0, SEEK_END); //파일포인터 fp를 파일의 젤 끝으로 보낸다.
	size = ftell(fp);		//파일포인터 fp가 가리키고 있는 값이 리턴된다. 

	buf = (char*)malloc(sizeof(char) * (size + 1));
	buf[size] = '\0';

	fseek(fp, 0, SEEK_SET); //파일포인터를 파일의 가장 처음으로 보낸다.
	fread(buf, size, 1, fp);

	puts(buf);
	fclose(fp);
	free(buf);
}

void PrintMenu() {
	printf("1. 신규회원 저장\n2. 회원정보 수정\n3. 회원 삭제\n");
	printf("4. 모든 회원 리스트\n5. 종료\n입력하세요> ");
}	

int main() {
	FILE *fp;
	int order = 0, loop = 1;

	while(loop) {
		PrintMenu();
		scanf("%d", &order);

		switch(order) {
			case 1: Save_Info(fp); break;
			case 2: Modify_Info(fp); break;
			case 3: Del_Info(fp); break;
			case 4: Print_List(fp); break;
			case 5: loop = 0; break;
			default: printf("Wrong input...\n");
		}
	}
	

	return 0;
}
