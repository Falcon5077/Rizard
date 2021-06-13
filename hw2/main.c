#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_AGE 200 //저장할수있는 나이 최댓값
#define MAX_MEMBER 200 //저장할수있는 멤버목록 최댓값

FILE *fp; //파일포인터변수 fp 선언

typedef struct member_list{ //회원정보 저장할 구조체
	char name[255]; //회원이름
	char age[10]; //회원나이
	char email[255]; //회원이메일
}member_list;

member_list list[MAX_MEMBER]; //회원정보 저장할 구조체배열 선언
int count = 0; //저장된 회원 인원수를 셀 count변수 선언 및 초기화

int inspect_email(int num){ 
//email이 올바르게 입력되었는지 검사하는 함수 num+1번째 회원의 이메일을 검사, 이때의 num을 매개변수로 받음
	int net=1, dot=1; //net, dot변수 초기화, 각각 @, .이 제대로 입력되었는지 검사 후 결과값 저장
	int len = strlen(list[num].email); //이메일 길이를 len변수에 저장

	for(int i=0; i<len; i++){ //문자열email의 첫번째글자부터 마지막까지 반복구문으로 검사함
		if(list[num].email[i]=='@' && 0<i){ //email에 @가 있고, 첫번째단어에 오지않을경우
			net=0;//@검사 변수에 0 저장
			for(int j=i+2; j<len; j++){ //@다음으로 .이 나오는지 검사. 이때 @바로다음에.이 나오는 경우는 에러이므로 i+2번째부터 검사함
				if(list[num].email[j] =='.' && j <len -1){ //email에.이 있고, 그 점이 email의 마지막단어가 아닌경우
					dot=0; //.검사 변수에 0 저장
					break; //반복구문 탈출
				}
			}
			break; //반복구문 탈출
		}
	}
	
	if(dot==0&&net==0) //두 검사변수 모두 0인경우에
		return 0; //0반환
	else
		return 1; //아닌경우 1 반환
}

void save_txt(){ //구조체에있는 데이터를 txt파일에 덮어쓰는 함수
	int i=0; //변수 i 선언
	remove("member_list.txt");

	fp=fopen("member_list.txt", "wt"); //파일내용이 있고없고에 상관없이 덮어쓰는 wt모드로 파일을 염
	if(fp==NULL){ //파일을 열때 에러가 날 경우
		fprintf(stderr, "회원정보리스트 member_list.txt.를 열 수 없습니다.\n"); //에러메시지 출력
		exit(0);
	}

	while(i!=count){ //count번째까지 while반복구문통해 덮어씀
		fprintf(fp, "%s / %s / %s\n", list[i].name, list[i].age, list[i].email); //데이터를 name / age / email\n형식으로 txt에저장
		i++; //다음 count로 넘어가기위해 i+1
	}

	fclose(fp); //덮어쓰기가 끝나면 파일을 닫음
}

void append_list(){ //신규회원 저장함수
	char ch; //계속 입력을 받을지 유무를 결정하는 변수 ch 선언
	int age; //문자열 나잇값을 정수형 변환위해 변수 age 선언

	fp=fopen("member_list.txt", "a+t"); //이어쓰는 모드로 파일 오픈
	if(fp==NULL){ //파일에러 났을때
		fprintf(stderr, "회원정보리스트 member_list.txt를 열 수 없습니다.\n"); //에러메시지 출력
		exit(0);
	}

	do{
		printf("이름: ");
		scanf(" %[^\n]", list[count].name); //이름을 개행전까지 입력받아 구조체에 저장

		printf("나이: ");
		scanf(" %s", list[count].age); //나이를 구조체에 저장
		age=atoi(list[count].age); //문자열변수age를 정수형으로 변환해 정수형변수age에 저장
		if(age>= MAX_AGE){ //age가 최대 나이보다 클 때
			while(age>=MAX_AGE){ //최대나이보다 작아질때까지 반복
				printf("나이는 200세를 넘길 수 없습니다. 다시 입력하세요.\n"); //경고문구 출력
				printf("나이: ");
				scanf(" %s", list[count].age); //나이를 다시 입력받음
				age=atoi(list[count].age); //다시 입력받은 값을 정수형변수 age에 저장해 다시 비교
			}
		}

		printf("이메일: ");
		scanf(" %[^\n]", list[count].email); //이메일을 구조체에 저장
		list[count].email[strlen(list[count].email)]='\0'; //회원 마지막 문장 끝 알림
		while(inspect_email(count)!=0){ //이메일 검사함수의 반환값이 0이 아니면 잘못 입력된것이므로 다시 입력받음
			list[count].email==NULL; //잘못 입력받은 이메일배열을 비워줌
			printf("이메일을 잘 못 입력하셨습니다. 다시입력하세요!\n");
			printf("이메일: ");
			scanf(" %[^\n]", list[count].email); //다시 이메일을 구조체에 저장
			list[count].email[strlen(list[count].email)]='\0'; //회원 마지막 문장 끝 알림
		}

		fprintf(fp, "%s / %s / %s\n", list[count].name, list[count].age, list[count].email); //입력받은 변수들을 파일에 저장
		count ++; //한명이 추가되었으므로 count변수에 1 추가한다.

		printf("계속 입력 할까요?(Y/N) "); //계속 입력을받을지 유무를 물어봄
		scanf(" %c", &ch); //받은값을 ch에 저장
		printf("\n"); //가독성을 위해 개행문자 출력
	}while(ch!='N'); //ch가 N일때 반복구문 탈출하면서 더이상 신규회원저장을 안받음
	printf("입력이 완료되었습니다.\n\n"); //입력이 완료되었단 문구 출력

	fclose(fp); //신규회원추가가 끝나고 파일을 닫음
}

void change_member(){ //회원정보 수정함수
	char buf_name[255]; //수정할 사람 이름을 받을 변수 buf_name선언
	int i=0, age=0; //반복구문과 나이검사를 위한 변수 i, age 선언

	printf("수정할 사람 이름을 입력해주세요: ");
	scanf(" %[^\n]", buf_name); //buf_name에 수정할 사람을 입력 받음

	for(i=0; i<count; i++){
		if(strcmp(list[i].name, buf_name)==0){ //반복구문통해 입력받은 이름이 구조체에 있는지 확인
			printf("사용자 %s 을 수정합니다.\n", buf_name); //있으면 수정을 시작한다

			printf("이름: "); 
			scanf(" %[^\n]", list[i].name); //수정한 이름을 입력받음

			printf("나이: ");
			scanf(" %s", list[i].age); //수정한 나이를 입력받음
			age=atoi(list[i].age); //나이검사를 위해 입력받은 나이의 문자열변수를 정수형으로 변환하여 정수형변수에 저장
			if(age>=MAX_AGE){ //나이가 최대나이를 넘길시
				while(age>=MAX_AGE){
					printf("나이는 200세를 넘길 수 없습니다. 다시 입력하세요.\n"); //오류 문구 출력
					printf("나이: ");
					scanf(" %s", list[i].age); //나이를 다시 입력받음
					age=atoi(list[i].age); //입력받은 나이를 다시 정수형으로 변환해 검사
				}
			}

			printf("이메일: ");
			scanf(" %[^\n]", list[i].email); //수정한 이메일을 입력받음
			while(inspect_email(i) !=0){ //이메일 검사함수의 반환값이 0이 아니면 잘못 입력된것이므로 다시 입력받음
				list[i].email==NULL; //잘못 입력된 이메일배열을 비워준다
				printf("이메일을 잘 못 입력하셨습니다. 다시 입력하세요!\n"); //오류 문구 출력
				printf("이메일: ");
				scanf(" %[^\n]", list[i].email); //다시 이메일을 구조체 저장
			}

			save_txt(); //수정한 내용을 파일에 덮어쓰기위해 덮어쓰는 함수 출력
			printf("수정 완료 되었습니다.\n\n"); //수정이 완료되었다는 문구 출력

			return; //함수 종료
		}
	}
	printf("사용자 %s 은 없습니다.\n\n", buf_name); //수정할대상이 없을시 문구 출력

	return; //함수 종료
}

void del_member(){ //회원정보 삭제함수
	int j=0, i=0; //변수 i, j선언
	char buf_name[255]; //삭제할 사람 이름을 받을 변수 선언

	printf("삭제할 사람 이름을 입력해주세요: ");
	scanf(" %[^\n]", buf_name); //buf_name변수에 삭제할 사람의 이름을 받음

	for(i=0; i<count; i++){
		if(strcmp(list[i].name, buf_name)==0){ //입력받은 이름이 구조체에 있을시
			printf("사용자 %s 을 삭제합니다.\n", buf_name); //사용자를 삭제한다

			for(j=i; j<count; j++){ //반복구문을 통해 삭제할대상의 다음 값을 구조체배열 한칸씩 댕겨와 원하는회원을 삭제한다.
				list[j] = list[j+1];
			}
			count --; //회원이 한명 삭제되었으므로 count변수에 -1을한다.
			save_txt(); //삭제한 내용을 파일에 덮어쓰기위해 덮어쓴는 함수를 출력한다.
			printf("삭제 완료 되었습니다.\n\n"); //삭제가 완료되었다는 문구 출력

			return; //함수 종료
		}
	}
	printf("사용자 %s 은 없습니다.\n\n", buf_name); //삭제할대상이 없을시 문구 출력

	return; //함수 종료
}

void print_list(){ //회원리스트 출력함수
	char buffer[sizeof(member_list)]; //파일내용을 임시로 저장할 문자열변수 선언
	
	fp=fopen("member_list.txt", "rt"); //파일을 읽기모드로 오픈한다
	if(fp==NULL){ //파일을 열때 에러발생할 시
		fprintf(stderr, "회원정보리스트 member_list.txt를 열 수 없습니다.\n"); //에러문구 출력
		exit(0);
	}

	while(fgets(buffer, sizeof(member_list), fp)){ //파일의 내용을 member_list의 사이즈만큼 buffer에 불러온다.(파일이 끝날때까지)
		fprintf(stdout, "%s", buffer); //터미널에 buffer의 값을 출력
	}
	fprintf(stdout, "\n\n"); //파일내용출력이 끝날 시 가독성을 위해 개행문자를 두번입력
	fclose(fp); //파일을 닫는다
}

void init(){ //프로그램 실행 시 txt파일이 비었으면 초기 데이터를 넣어줌
	int i=0; //정수형변수 i선언

	fp=fopen("member_list.txt", "a+t"); //파일을 읽고쓸수있는 모드로 연다
	if(fp==NULL){ //파일을 열때 에러 발생시
		fprintf(stderr, "회원정보리스트 member_list.txt를 열 수 없습니다.\n"); //에러문구를 출력함
		exit(0);
	}

	i=getc(fp); //파일의 내용에 첫번째 문자를 받아오는데, 반환값을 변수 i에 저장한다.
	if (i==-1){ //파일에 내용이 없어 -1을 반환할때 아래의 초기데이터를 파일에 넣어준다.
		fprintf(fp, "PARK GIL DONG / 22 / parkpark@hotmail.com\n"); //박길동 회원의 정보를 파일에 저장
		fprintf(fp, "LEE GIL DONG / 23 / gildonglee@naver.com\n"); //이길동 회원의 정보를 파일에 저장
	}
	
	fclose(fp); //파일을 닫는다
}

void load_list(){ //프로그램 실행 시 txt파일에 list가 있으면 로드함
	int i=0; //정수형 변수 i 선언

	fp=fopen("member_list.txt", "rt"); //파일을 읽기모드로 연다
	if(fp==NULL){ //파일을 열때 에러 발생시
		fprintf(stderr, "회원정보리스트 member_list.txt를 열 수 없습니다.\n"); //에러문구 출력
		exit(0);
	}

	while(feof(fp)==0){ //파일의 끝까지 반복함
		i=0; //변수 i 초기화
		char tmp[1024]; //문자열변수 tmp선언
		char tmp2[1024]; //문자열변수 tmp2선언

		fscanf(fp, "%[^\n]\n", tmp); //개행문자 전까지 파일의 값을 tmp로 받아옴
		strcpy(tmp2, tmp); //tmp의 내용을 tmp2에 복사

		char* ptr = strtok(tmp2, "/"); //tmp2를 /를 기준으로 잘라서 ptr에 반환
		while(ptr){ //자른문자열이 나오지 않을때까지 반복
			if(i==0){ //처음 반복시
				strcpy(list[count].name, ptr); //ptr 값을 count변째 name변수에 복사
				list[count].name[strlen(list[count].name)-1]='\0'; // /전까지 저장되어 공백도 저장되므로 공백을 지워준다
			}
			else if(i==1){ //두번째 반복시
				strcpy(list[count].age, ptr); //ptr값을 count번째 age변수에 복사
				for (int k=0; k<strlen(list[count].age)-1; k++){ // 앞뒤의 공백도 같이 저장되므로 공백을 지워준다
					list[count].age[k] = list[count].age[k+1]; //앞의 공백을 지우기 위해 한칸씩 댕겨옴
				}
				list[count].age[strlen(list[count].age)-2]='\0'; //뒤의 공백을 지워줌
			}
			else{ //세번째 반복시
				strcpy(list[count].email, ptr); //ptr값을 count번째 email변수에 복사
				for(int k=0; k<strlen(list[count].email)-1; k++){ //마찬가지로 앞의 공백을 지워준다.
					list[count].email[k]=list[count].email[k+1]; //앞의 공백을 지우기 위해 한칸씩 댕겨옴
					if(k==strlen(list[count].email)-2)
						list[count].email[k+1]='\0';
				}
			}

			ptr=strtok(NULL, "/"); //다음 문자열을 잘라서ptr에 반환
			i++; //반복을 위해 변수i에 1을 더함
		}
		count++; //그다음 줄을 저장하기 위해 count변수에 1을 추가한다.
	}

	fclose(fp); //파일을 닫는다.
}

void menu(){ //메뉴함수
	int choice; //선택받은 메뉴값을 저장할 변수 선언
	do{
		printf("1. 신규회원 저장\n");
		printf("2. 회원정보 수정\n");
		printf("3. 회원 삭제\n");
		printf("4. 모든 회원 리스트\n");
		printf("5. 종료\n");
		printf("입력하세요>");
		scanf(" %d", &choice); //원하는 메뉴값을 입력받아 choice변수에 저장한다

		switch(choice){
			case 1: append_list();break; //1번일때 신규회원저장함수 호출
			case 2: change_member();break; //2번일때 회원정보수정함수 호출
			case 3: del_member();break; //3번일때 회원삭제함수 호출
			case 4: print_list();break; //4번일때 회원리스트출력함수 호출
			case 5: printf("\n종료합니다.\n"); return; //5번일때 종료합니다 문구 출력
			default: printf("번호를 다시한번 확인해주세요.\n"); //그 외의 값을 입력받을때 에러문구를 출력한다.
		}

	}while(choice!=5); //종료를하기위해 5를 입력하기 전까지 반복
}

int main(int argc, char*argv[]){
	init(); //초기화함수 호출
	load_list(); //실행 시 파일에있는 내용을 구조체배열에 저장하기 위해 로드함수 호출
	menu(); //메뉴함수 호출

	return 0; //프로그램 종료
}

