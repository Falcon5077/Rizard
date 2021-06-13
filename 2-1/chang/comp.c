#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Save_Info(FILE *fp) { //이용자로부터 정보를 입력받아 txt파일에 저장한다.
	char name[255];
	char email[255];
	char ch;
	char *dot, *gol;
	int age = 0, loop = 1;

	fp = fopen("Info.txt", "a"); //추가쓰기 모드로 Info.txt파일을 연다.

	if(fp == NULL) { //만약 파일포인터가 NULL이라면 파일을 열지 못한것이므로 오류메시지 출력
		fprintf(stderr, "파일을 열 수 없습니다.\n");
	} else { //파일열기에 성공했다면,
		do{ //이름, 나이,이메일을 물어서 각각 변수에 저장한다.
			printf("이름: ");
			scanf(" %[^\n]s", name);
			
			printf("나이: ");
			scanf(" %d", &age);
			
			while(loop) { //이메일을 입력받고 해당 문자열에 @와 .이 없는지를 검사한다.
				printf("이메일: ");
				scanf(" %s", email);
				gol = strstr(email, "@"); //해당 문자열에 @가 없으면 NULL반환
				dot = strstr(email, "."); //해단 문자열에 .이 없으면 NULL반환
				if(gol != NULL) { //@와 . 둘중 하나라도 없으면 이용자에게 다시 입력할것을 요청
					if(dot != NULL)
						loop = 0;
					else printf("이메일은 @와 .이 포함되어 있어야 합니다.\n");
				}else printf("이메일은 @와 .이 포함되어 있어야 합니다.\n");
			} loop = 1; //해당 문자열에 @와 .이 모두 있으면 루프탈출

			fprintf(fp, "%s / %d / %s\n", name, age, email); //fprintf를 이용해 순서대로 이름과 나이 이메일을 기록한다.
			printf("계속 입력 할까요?(Y/N) "); //계속 입력할지를 묻는다.
			scanf(" %c", &ch);
			printf("\n");
		} while (ch != 'N');
		printf("입력이 완료되었습니다.\n\n");
		fclose(fp); //완료 후 파일 닫기
	}
}

void Del_Info(FILE *fp) { //파일에서 특정값을 삭제
	char *buf;
	char *p;
	char order[255];
	int size = 0, k = 1;

	printf("삭제할 사람 이름을 입력해주세요: "); //삭제할 사람 이름을 입력받아 order에 저장
	scanf(" %[^\n]s", order);
	fp = fopen("Info.txt", "r+t"); //Info.txt파일을 r+t, 읽기우선 쓰기 모드로 open
	if(fp == NULL) { //파일이 제대로 열리지 않았을때 오류메시지 출력
		fprintf(stderr, "파일을 열 수 없습니다.\n");
	}
	
	fseek(fp, 0, SEEK_END); //파일포인터 fp를 문자열 가장 끝으로 이동
	size = ftell(fp); //size에 fp위치(문자열 끝)값 저장

	buf = (char*)malloc(sizeof(char) * (size + 1)); //size+1(\0값 들어갈 위치 확보)크기만큼 buf 할당
	buf[size] = '\0'; //젤 마지막에 문자열 끝남 표시 '\0'입력
	
	fseek(fp, 0, SEEK_SET); //fp를 문자열 가장 앞으로 이동
	fread(buf, size, 1, fp); //파일에서 문자열을 size크기만큼 읽어 buf에 저장
	p = strstr(buf, order); //buf와 order를 비교해서 order값이 buf에 없다면 NULL을 반환, 있다면 그 주소값을 반환

	if (p == NULL) { //p가 NULL이라면 일치하는 내용이 없으므로 그 내용을 출력
		printf("사용자 %s는 없습니다.\n\n", order);
		free(buf); //동적할당했던 buf free
		fclose(fp); //파일 닫기
	}
	else { //일치하는 값이 있다면
		for(int i = 0; k != 0; i++) { //일치하는 문자열 시작위치~ '\n'줄바꿈 문자까지 \b로 치환
			if(p[i] == '\n') k = 0; 
			p[i]  = '\b';
		}
		fseek(fp, 0, SEEK_SET); //파일 젤앞으로 fp이동
		fprintf(fp, "%s", buf); //buf에서 수정된 내용을 파일에 기록
		printf("삭제가 완료되었습니다.\n\n");
		fclose(fp);
		free(buf);
	}
}

void Modify_Info(FILE *fp) { //특정 위치의 값을 수정
	char *buf;
	char *p, *gol, *dot;
	char order[255], name[255], email[255];
	int size = 0, k = 1, age = 0, loop = 1;

	printf("수정할 사람 이름을 입력해주세요: "); //수정할 사람이름을 받아 order에 대입
	scanf(" %[^\n]s", order);
	fp = fopen("Info.txt", "r+t"); //파일을 읽기우선기록모드로 연다.
	
	fseek(fp, 0, SEEK_END); //fp를 가장 문자열 가장뒤로 이동
	size = ftell(fp); //가장 뒤의 위치값을 size에 반환

	buf = (char*)malloc(sizeof(char) * (size + 1)); //buf를 size+1크기로 할당
	buf[size] = '\0'; //buf젤 마지막 위치에 \0대입
	
	fseek(fp, 0, SEEK_SET); 
	fread(buf, size, 1, fp);
	p = strstr(buf, order); //buf에서 order값이 있는지 탐색

	if (p == NULL) { //order와 일치하는 값이 없을경우 NULL을 받고 그 메시지를 출력
		printf("사용자 %s는 없습니다.\n\n", order);
		free(buf);
		fclose(fp);
	}
	else { //일치하는 값이 있을 경우 그 값의 처음 위치값을 받고 아래를 실행
		printf("사용자 %s 을 수정합니다.\n", order);
		for(int i = 0; k != 0; i++) { //받은 위치값으로부터 줄바꿈 까지 값을 모두 삭제
			if(p[i] == '\n') k = 0;
			p[i]  = '\b';
		}
		fseek(fp, 0, SEEK_SET);
		fprintf(fp, "%s", buf); //삭제한 값을 파일에 저장 
		//이후 수정할 이름, 나이, 이메일값을 입력받아 각 변수에 저장한다.
		printf("이름: "); 
		scanf(" %[^\n]s", name);
		
		printf("나이: ");
		scanf(" %d", &age);

		while(loop) { //SaveInfo에서와 마찬가지로 @와 .이 있는지 검사해서 입력받는다.
			printf("이메일: ");
			scanf(" %s", email);
			gol = strstr(email, "@");
			dot = strstr(email, ".");
 			if(gol != NULL) {
				if(dot != NULL)
					loop = 0;
				else printf("이메일은 @와 .이 포함되어 있어야 합니다.\n");
			}else printf("이메일은 @와 .이 포함되어 있어야 합니다.\n");
		} loop = 1;

		fprintf(fp, "%s / %d / %s\n", name, age, email); //입력된 값들을 순서대로 파일에 넣는다.
		printf("수정 완료 되었습니다.\n\n");
		fclose(fp);
		free(buf);
	}
}

void Print_List(FILE *fp) { //파일이 가지고 있는 값들을 출력
	char *buf;
	int size;

	fp = fopen("Info.txt", "r");
	
	fseek(fp, 0, SEEK_END); //파일포인터 fp를 파일의 젤 끝으로 보낸다.
	size = ftell(fp);		//파일포인터 fp가 가리키고 있는 값이 리턴된다. 

	buf = (char*)malloc(sizeof(char) * (size + 1));
	buf[size] = '\0';

	fseek(fp, 0, SEEK_SET); //파일포인터를 파일의 가장 처음으로 보낸다.
	fread(buf, size, 1, fp); //buf에 값들을 size크기만큼 읽어서 저장

	puts(buf); //puts함수를 이용해 buf값을 출력
	fclose(fp); //파일닫기
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
			case 5: loop = 0; printf("\n종료합니다.\n\n"); break;
			default: printf("Wrong input...\n");
		}
	}
	return 0;
}
