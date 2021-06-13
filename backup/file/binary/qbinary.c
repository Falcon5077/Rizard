#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUF 8192

// 사용할 함수 선정의
int addUser();
int printProgram();
int printUser();

char* fileName = "database.bin";

int main(int argc, char* argv[])
{
	int a;						// 선택한 숫자 저장하는 변수
	char buf[MAX_BUF];			// 8192 사이즈의 버퍼 생성
	
	while(1){
		int a = printProgram();
		if( a == 3){
			fprintf(stdout,"프로그램을 종료합니다. \n");
			break;
		}

		switch(a)	// 선택한 값으로 switch문 실행
		{
			case 1:	// 1. 추가
				addUser();
				break;
			case 2:	// 2. 출력
				printUser();
				break;
		}
	}// while문 반복
	

	return 0;
}

int addUser()	// 유저를 추가하는 함수
{
	FILE* target = fopen(fileName,"wb"); // 쓰기모드 바이너리모드로 파일을 오픈
	
	char name[255];				//이름
	unsigned char age;			//나이
	unsigned short int HP;		//HP
	double x,y;					//x y 좌표
	char* buf;					//버퍼
	char ans;					//동맹 추가 입력 여부 Y / N

	getchar();
	fprintf(stdout,"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
	fprintf(stdout,"A 이름 : ");
	scanf("%[^\ns]", &name[0]);
	int len = strlen(name);		// 입력받은 값의 길이를 받아서
	fwrite(&len,sizeof(int),1,target);	// 그 길이를 파일에 저장하고
	fwrite(name,sizeof(char),len,target);	// 이름도 그 길이만큼 저장

	do{
		getchar();
		fprintf(stdout,"B 나이 : ");
		scanf("%hhu", &age);
		if(age > 0 && age < 128)	// 1~127 사이의 값을 입력할때까지 while문 반복
		{
			fwrite(&age,sizeof(unsigned char),1,target);
			// 제대로 입력했다면 나이를 파일에 저장
			break;
		}
		fprintf(stdout,"B 나이 (0~127) : ");
	}while(1);		

	getchar();
	fprintf(stdout,"C HP : ");
	scanf("%hd",&HP);
	fwrite(&HP,sizeof(unsigned short int),1,target);

	getchar();
	fprintf(stdout,"D 좌표 x : ");
	scanf("%lf",&x);
	fwrite(&x,sizeof(double),1,target);

	fprintf(stdout, "D 좌표 y : ");
	scanf("%lf",&y);
	fwrite(&y,sizeof(double),1,target);

	while(1)
	{
		fprintf(stdout, "동맹 ID를 입력하세요 : ");
		scanf("%s",&name[0]);
//		int temp = 1;
//		fwrite(&temp,sizeof(int),1,target);

		len = strlen(name);
		fwrite(&len,sizeof(int),1,target);
		fwrite(name,sizeof(char),len,target);

		fprintf(stdout, "동맹을 계속 추가할까요? ");
		getchar();
		scanf("%c",&ans);

		if(ans == 'N')
			break;

	}

	
	fclose(target);
	return 0;
}

int printProgram()	// 선택한 값을 리턴해준다
{
	int a;
	fprintf(stdout,"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
	fprintf(stdout,"1. 플레이어 정보 기록\n");
	fprintf(stdout,"2. 플레이어 정보 확인\n");
	fprintf(stdout,"3. 종료\n");
	fprintf(stdout,"입력하세요> ");

	while(1)
	{
		scanf("%d",&a);
		if(a > 3){	// 3보다 큰 수를 입력하면 재입력 요청
			fprintf(stdout,"다시 입력하세요> ");
			getchar();	// 버퍼를 비워준다
			continue;
		}
		break;
	}
	return a;
}

int printUser()
{
	FILE* fp = fopen(fileName,"rb");
	char str[8192];
	int num;
	unsigned char age;
	int value;
	int len;

	if(fp == 0)
	{
		return -1;
	}
	fprintf(stdout,"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");

	fread(&len,sizeof(int),1,fp);		// 이름의 길이

	fread(str,sizeof(char),len,fp);	
	// len만큼 이름을 읽어서 str에 저장
	printf("ID : %s / ",str);

	fread(&age,sizeof(unsigned char),1,fp);	// 나이
	printf("나이 : %hhu / ",age);

	fread(&value,sizeof(unsigned short int),1,fp);	//HP
	printf("HP : %d / ",value);

	double pos;	
	fread(&pos,sizeof(double),1,fp);	// 좌표 X
	printf("좌표 : %.3lf , ",pos);
	
	fread(&pos,sizeof(double),1,fp);	// 좌표 Y
	printf("%.3lf \n",pos);

	char* buffer = malloc(sizeof(char)* 1024);	// 동맹이름을 저장할 버퍼
	char* field = " / ";	// 동맹의 필드를 구분해줄 문자열
	int count;	// 동맹의 수
	while(1){
		len = 0;
		fread(&len,sizeof(int),1,fp);
		if(len == 0)
			break;
		fread(str,sizeof(char),len,fp);

		// count가 0일때 아래 코드가 실행되면
		if(count++ != 0)	// "/ 1 / 2 / 3" 으로 저장되므로 맨 처음의 경우는 제외하기 위한 if문
			strcat(buffer,field);

		strcat(buffer,str);
	}

	printf("등록된 동맹 수 : %d \n",count);
	printf("%s \n",buffer);

	free(buffer);
	fclose(fp);

	return 0;
}
