#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE *fp;
	int number;
	char name[30];
	int score;
	char ch;

	fp=fopen("scores.txt", "w");
	if(fp==NULL) {
		fprintf(stderr, "성적 파일 scores.txt를 열 수 없습니다.\n");
		exit(0);
	}

	do{
		printf("\n 학번:");
		scanf("%d", &number);
		printf("이름:");
		scanf("%s", name);
		printf("성적:");
		scanf("%d", &score);

		fprintf(fp, "%d %s %d", number, name, score);
		printf("추가계속?(y/n)");
		scanf("%c", &ch);
	}while(ch!='n');

	fclose(fp);
	return 0;
}
