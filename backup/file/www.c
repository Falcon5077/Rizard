#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#define MAX_BUF 8192

int printProgram();
int initProgram(FILE* target,int isAdd);
int printAllUser();
int findUser(int isDel);

int main(int argc, char* argv[])
{
	int a;						//선택한 숫자 저장하는 변수
	char buf[MAX_BUF];			//8192 사이즈의 버퍼 생성
	char* fileName = "database.txt";	// 유저 정보를 저장하는 파일 이름

	//file open
	FILE *targetFile = fopen(fileName,"at");	//이어쓰기 모드로 파일 오픈	

	//오픈 실패시 출력
	if(targetFile == NULL)
	{
		printf("파일 생성 또는 읽기 실패\n");
		return -1;
	}

	while(1){
		int a = printProgram();	// 선택지를 출력하는 함수를 실행하고 그 값을 a에 저장
		targetFile = fopen(fileName,"at");
		if( a == 5)
			break;
	switch(a)
	{
		case 1:
			initProgram(targetFile,1);
			break;
		case 2:
			if(findUser(0) == 1){
				targetFile = fopen(fileName,"at");
				initProgram(targetFile,0);
			}
			break;
		case 3:
			findUser(1);
			break;
		case 4:
			printAllUser();
			break;
	}
	fclose(targetFile);	
	}
	
	//file close
	fclose(targetFile);

	return 0;
}

int printProgram()
{
	int a;
	fprintf(stdout,"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
	fprintf(stdout,"1. 신규회원 저장\n");
	fprintf(stdout,"2. 회원정보 수정\n");
	fprintf(stdout,"3. 회원 삭제\n");
	fprintf(stdout,"4. 모든 회원 리스트\n");
	fprintf(stdout,"5. 종료\n");
	fprintf(stdout,"입력하세요> ");
	scanf("%d",&a);

	return a;
}

int initProgram(FILE* target,int isAdd)
{
	char name[255];
	int age;
	char email[255];
	char ans;
	
	while(1){
		getchar();
		fprintf(stdout,"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
		fprintf(stdout,"A 이름: ");
		scanf("%[^\n]s",&name[0]);
		
		do{
			getchar();
			fprintf(stdout,"B 나이(0~200): ");
			scanf("%d",&age);
		}while(age > 200 || age < 0);

		while(1){
			getchar();
			fprintf(stdout,"C 메일: ");
			scanf("%s",&email[0]);
			char* check = strchr(email,'@');
			if(check != NULL)
			{
				if(strchr(check,'.') != NULL)
				{
					break;
				}
			}
			fprintf(stdout,"이메일 형식이 올바르지 않습니다 \n");
		}

		fprintf(target,"%s / %d / %s\n",name,age,email);
		getchar();

		if(isAdd == 0){
			fprintf(stdout,"수정완료되었습니다\n");
			return 0;
		}

		fprintf(stdout,"계속 입력할까요?(Y/N)");
		scanf("%c",&ans);

		if(ans == 'Y')
			continue;
		else if(ans == 'N')
			break;
	}

}

int printAllUser()
{
	FILE* target = fopen("database.txt","r");
	char buf2[MAX_BUF];
	int lineCount = 1;
	int i = 1;
	if(target == NULL)
	{
		return -1;
	}
	fprintf(stdout,"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
	fprintf(stdout," 회원\t리스트 \n");

	int result = fread(buf2,1,MAX_BUF,target);
	fwrite(buf2,1,result,stdout);

	fclose(target);
}

int findUser(int isDel)
{
    FILE* target = fopen("database.txt","rwt");

    char buf2[MAX_BUF];
	char newBuf[MAX_BUF] = "";
	int lineCount = 1;
    int i = 1;
	int notNull = 0;

	char findStr[100];
	char* all = "";

	if(isDel == 0)
		printf("수정할 사람 이름을 입력해주세요: ");
	else if(isDel == 1)
		printf("삭제할 사람 이름을 입력해주세요: ");
	
	getchar();
	scanf("%[^\n]s",findStr);

    if(target == NULL)
    {
        return -1;
    }
	char* str;
    while(!(feof(target)))
    {
        if(fread(&buf2,1,1,target) == 0 )break;
        else fseek(target,-1, SEEK_CUR);

        fgets(buf2,sizeof(buf2),target);
		str = strstr(buf2,findStr);

		if(str !=  NULL){
			notNull = 1;
			printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
			if(isDel == 0)
				printf("%s의 정보를 수정합니다.\n",str);	
			else if(isDel == 1)
				printf("%s의 정보를 삭제합니다.\n",str);
			continue;
		}
		else{
			all = strcat(newBuf,buf2);		
		}
    }

	if(notNull == 0)
	{
		printf("사용자 %s 는 없습니다.\n",findStr);
		fclose(target);
		return 0;
	}

    fclose(target);
	target = fopen("database.txt","wt");
	fprintf(target,"%s",all);
	fclose(target);

	return 1;
}


