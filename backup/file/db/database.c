#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#define MAX_BUF 8192
#define ADD 1
#define DEL 1

//사용할 함수 원형 선언
int printProgram();	// 선택문 출력함수
int addUser(FILE* target,int isAdd); // 유저 추가 함수
int printAllUser();	//	전체 유저 출력 함수
int findUser(int isDel);	// 수정,삭제 함수

int main(int argc, char* argv[])
{
	int a;						// 선택한 숫자 저장하는 변수
	char buf[MAX_BUF];			// 8192 사이즈의 버퍼 생성
	char* fileName = "database.txt";	// 유저 정보를 저장하는 파일 이름
	FILE *targetFile = fopen(fileName,"at");			// database.txt 파일 오픈
	
	//오픈 실패시 출력
	if(targetFile == 0)
	{
		fprintf(stdout,"파일 생성 또는 읽기 실패\n");
		return -1;
	}
	fclose(targetFile); //다시 닫아줌

	while(1){
		int a = printProgram();	// 선택지를 출력하는 함수를 실행하고 그 값을 a에 저장
		targetFile = fopen(fileName,"at");	// 이어쓰기모드로 파일오픈
		if( a == 5){	// 5를 입력했다면 프로그램 종료
			fprintf(stdout,"프로그램을 종료합니다. \n");
			break;
		}

	switch(a)	// 선택한 값으로 switch문 실행
	{
		case 1:	// 1. 추가
			addUser(targetFile,ADD);// 추가 모드로 addUser 실행
			break;
		case 2:	// 2. 수정
			//findUser는 0과 1을 리턴하는데 0은 유저를 찾지못했을때 1은 유저를 찾고 삭제
			if(findUser(0) == 1){	// 유저를 찾고 삭제했다면
				targetFile = fopen(fileName,"at");	// 파일을 열어서 
				addUser(targetFile,0);	// 새로운 유저 추가
			}							// 유저검색 -> 삭제 -> 추가가 결국 수정이기 때문
			break;
		case 3:	// 3. 삭제
			findUser(DEL);	// 유저를 찾아서 삭제하는 함수
			break;
		case 4://  4. 회원리스트
			printAllUser(); // db파일 전체출력하는 함수
			break;
	}
	fclose(targetFile);	// 파일종료
	}// while문 반복
	
	//file close
	fclose(targetFile); // 파일종료하지않고 break로 while문을 탈출하기때문에 종료

	return 0;
}

int printProgram()	// 선택한 값을 리턴해준다
{
	int a;
	fprintf(stdout,"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
	fprintf(stdout,"1. 신규회원 저장\n");
	fprintf(stdout,"2. 회원정보 수정\n");
	fprintf(stdout,"3. 회원 삭제\n");
	fprintf(stdout,"4. 모든 회원 리스트\n");
	fprintf(stdout,"5. 종료\n");
	fprintf(stdout,"입력하세요> ");

	while(1)
	{
		scanf("%d",&a);
		if(a > 5){	// 5보다 큰 수를 입력하면 재입력 요청
			fprintf(stdout,"다시 입력하세요> ");
			getchar();	// 버퍼를 비워준다
			continue;
		}
		break;
	}

	return a;
}

int addUser(FILE* target,int isAdd)	// User를 추가하는 함수
{
	//각종 정보 저장공간
	char name[255];
	int age;
	char email[255];

	//추가 입력 Y/N을 저장하는 char변수
	char ans;
	
	while(1){
		getchar();
		fprintf(stdout,"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
		fprintf(stdout,"A 이름: ");
		scanf("%[^\n]s",&name[0]);	// 줄바꿈기호가 나올때까지 문자열을 받는 다는 의미로
									// 띄어쓰기를 포함한 정보를 저장하게 됨
		
		do{
			getchar();
			fprintf(stdout,"B 나이(0~200): ");
			scanf("%d",&age);			// 나이를 age에 입력받는다
		}while(age > 200 || age < 0);	// 나이가 0살부터 200살까지 입력가능하며 
										// 그 외의 값을 입력하면 다시 반복하게 된다

		while(1){
			getchar();
			fprintf(stdout,"C 메일: ");
			scanf("%s",&email[0]);		// 이메일으르 email 에 입력받는다
			char* check = strchr(email,'@');	//먼저 @가 있는지 체크하고 찾은 위치를 리턴합니다.
			if(check != NULL)			// 비어있지 않다면 @가 있음을 알수있습니다.
			{
				if(strchr(check,'.') != NULL) // check에는 @의 위치의 포인터를 갖고 있으므로
				{							  // @부터 .이 있는지 다시 체크합니다.
					break;					  // @와 . 의 양식이 맞다면 while문을 탈출
				}
			}
			fprintf(stdout,"이메일 형식이 올바르지 않습니다 \n");
		}	// 이메일 양식이 올바르지않다면 메세지를 출력하고 while문 반복

		fprintf(target,"%s / %d / %s\n",name,age,email);	// 파일에 입력받은 데이터를 저장
		getchar();

		if(isAdd != ADD){	// 추가를 위해 호출된게 아니라 수정을 위해서 호출되었다면
			fprintf(stdout,"수정 완료되었습니다\n");
			return 0;		// 수정을 완료했다고 알리고 addUser 함수를 종료
		}

		// 수정을 위해 함수가 호출된게 아니라면 아래 코드 실행
		fprintf(stdout,"계속 입력할까요?(Y/N)");	
		scanf("%c",&ans);
		
		if(ans == 'Y')
			continue;
		else if(ans == 'N') // 입력값이 N이라면 추가를 멈추고 종료
			break;
	}

}

int printAllUser()
{
	FILE* target = fopen("database.txt","r");	// 읽기모드로 파일 오픈
	char buf2[MAX_BUF];
	if(target == NULL)
	{
		return -1;
	}
	fprintf(stdout,"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
	fprintf(stdout," 회원\t리스트 \n");

	int result = fread(buf2,1,MAX_BUF,target);	// 파일을 읽어서 buf2 버퍼에 저장
	fwrite(buf2,1,result,stdout);				// 읽은 버퍼를 stdout을 통해서 출력

	//file close
	fclose(target);
}

int findUser(int isDel)	// 입력받은 값으로 파일을 읽어서 삭제하는 함수
{
    FILE* target = fopen("database.txt","rt");	// 읽기우선 쓰기모드

    char buf2[MAX_BUF];			// 한 줄씩 읽을 때 저장할 버퍼
	char newBuf[MAX_BUF] = "";	// 
	int notNull = 0;			// 비어있는지 체크하는 변수 

	char findStr[100];			// 찾고자 하는 문자열을 저장할 변수
	char* all = "";				// newBuf의 주소를 저장할 포인터변수

	//삭제를 위해 호출된것인지 수정을 위해서인지 체크하는 코드
	if(isDel == 0)
		printf("수정할 사람 이름을 입력해주세요: ");
	else if(isDel == DEL)
		printf("삭제할 사람 이름을 입력해주세요: ");
	
	getchar();
	scanf("%[^\n]s",findStr);	// 띄어쓰기 포함 다음 찾고자 하는 문자열 저장

    if(target == NULL)
    {
        return -1;
    }

	char* str;
	
	while(!(feof(target))){				// 파일포인터가 문서 끝까지 갈 동안 반복하는 코드
		if(fgets(buf2,sizeof(buf2),target)==NULL) break;	// 마지막 줄 중복 출력 방지 코드
										// fgets로 줄바꿈까지 파일을 읽음 (한 줄을 읽음)
		str = strstr(buf2,findStr);		//읽어온 줄에 findStr이 포함되어있는지 체크

		if(str !=  NULL){	// 포함 되어있다면
			notNull = 1;	// notNull을 1로 바꿔서 비어있지않음을 체크 한 후
							// continue로 건너뛰어서 이 라인을 빼고 저장함 즉 삭제와 같음
			printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
			if(isDel == 0)
				printf("%s의 정보를 수정합니다.\n",findStr);	
			else if(isDel == 1)
				printf("%s의 정보를 삭제합니다.\n",findStr);
			continue;
		}
		else{	// 찾고자하는 문자가 없는 라인 즉, buf2 를 newBuf에 이어붙이고 그 주소를 all에 저장
			all = strcat(newBuf,buf2);		
		}
    }

	//notNumm 이 0이면 strstr로 찾지 못했기때문에 함수 종료
	if(notNull == 0)
	{
		printf("사용자 %s 는 없습니다.\n",findStr);
		fclose(target);
		return 0;
	}

	// 파일을 닫아주고 쓰기모드로 다시 오픈후 저장해둔 all을 파일에 덮어써줌
    fclose(target);
	target = fopen("database.txt","wt");
	fprintf(target,"%s",all);

	fclose(target);
	return 1;
}


