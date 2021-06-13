#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE * fp;

void write_file();


//플레이어 정보 저장 구조체
typedef struct player_inf{
	int len_ID; //플레이어 ID길이 저장변수
	char ID[255]; //플레이어 ID(최대 255자)
	int age; //플레이어 나이 (0-127)
	int HP; //플레이어 HP (0-65535)
	double pos_x; //플레이어 x좌표
	double pos_y; //플레이어 y좌표
	int count; //플레이어 동맹 인원
	int len_friend[255]; //동맹 이름 길이 저장변수
	char friend[255][255]; //플레이어 동맹 ID 리스트(최대 255명)
}player_inf;

//p1플레이어 선언
player_inf p1;

//정보를 입력받는 함수
void write_inf(){	
	char choice; //동맹반복 탈출위한 변수

	printf("ID를 입력하세요: ");
	scanf(" %s", p1.ID); //ID입력받음
	p1.len_ID = strlen(p1.ID); //플레이어 ID길이 저장변수에 길이저장

	printf("나이를 입력하세요: ");
	scanf("%d", &p1.age); //나이를 입력받음
	while(p1.age>127 && p1.age<0){ //나이가 0-127범위 밖일때 다시 입력받음
		printf("나이는 0-127까지만 입력이 됩니다. 다시입력하세요.\n");
		printf("나이를 입력하세요: ");
		scanf("%d", &p1.age);
	}

	printf("체력을 입력하세요: ");
	scanf("%d", &p1.HP); //체력 입력받음

	printf("X 좌표를 입력하세오: ");
	scanf("%lf", &p1.pos_x); //플레이어의 x좌표 입력받음
	printf("Y 좌표를 입력하세요: ");
	scanf("%lf", &p1.pos_y); //플레이어의 y좌표 입력받음
	
	p1.count = 0; //동맹친구 수를 0으로 초기화

	do{
		if(p1.count==255){ //동맹친구가 255명을 넘기면 에러문구 출력
			printf("동맹 목록이 이미 다찼습니다.\n");
			break;
		}

		printf("동맹 ID를 입력하세요: ");
		scanf(" %s", p1.friend[p1.count]); //동맹원 ID 입력받음
		p1.len_friend[p1.count]=strlen(p1.friend[p1.count]); //동맹원 ID 길이를 len_friend변수에 저장
	
		p1.count++; //동맹인원 count변수 +1
		
		printf("동맹을 계속 추가할까요?: ");
		scanf(" %c", &choice); //동맹인원을 계속 추가받을 시 Y, 안받을때 N을 받음
	}while(choice != 'N'); //N입력시 반복구문 탈출

	write_file(); //구조체내용을 바이너리파일에 저장하는 함수 호출
	
	printf("완료되었습니다.\n\n");
}

//구조체내용을 바이너리파일에 작성하는 함수
void write_file(){
	fp=fopen("player.bin", "wb"); //bin파일 쓰기모드로 open
	if(fp==NULL){ //에러발생시 에러문구 출력
		fprintf(stderr, "Error to open...\n"); 
		exit(1);
	}

	fwrite(&p1.len_ID, sizeof(int), 1, fp); //p1의 ID길이를 바이너리파일에 작성
	fwrite(&p1.ID, p1.len_ID, 1, fp); //p1의 ID를 바이너리파일에 작성
	fwrite(&p1.age, sizeof(p1.age), 1, fp); //p1의 나이를 바이너리파일에 작성
	fwrite(&p1.HP, sizeof(p1.HP), 1, fp); //p1의 체력을 바이너리파일에 작성
	fwrite(&p1.pos_x, sizeof(p1.pos_x), 1, fp); //p1의 x좌표를 바이너리파일에 작성
	fwrite(&p1.pos_y, sizeof(p1.pos_y), 1, fp); //p1의 y좌표를 바이너리파일에 작성
	fwrite(&p1.count, sizeof(p1.count), 1, fp); //p1의 count변수를 바이너리파일에 작성

	for(int k=0; k<p1.count; k++) //for 구문을 활용해 count만큼 동맹의 문자길이를 바이너리파일에 작성
		fwrite(&p1.len_friend[k], sizeof(int), 1, fp);

	for(int i=0; i<p1.count; i++) //for 구문을 활용해 count만큼 동맹인원을 바이너리파일에 작성
		fwrite(&p1.friend[i], p1.len_friend[i], 1, fp);

	fclose(fp); //파일을 닫음
}

//바이너리파일에 있는 내용을 구조체에 저장해 출력하는 함수
void print_inf(){
	fp=fopen("player.bin", "rb"); //bin파일 읽기모드로 open
	if(fp==NULL){ //에러발생시 에러문구 출력
		fprintf(stderr, "Error to open...\n");
		exit(1);
	}


	fread(&p1.len_ID, sizeof(int), 1, fp); //int 크기만큼 파일로부터 읽어와 p1.len_ID에 잦ㄱ성
	fseek(fp, 0, SEEK_CUR); //다음내용 읽기위해 위치를 현재위치로 조정
	fread(&p1.ID, p1.len_ID, 1, fp); //ID변수 크기만큼 파일로부터 읽어와 p1.ID에 작성
	fseek(fp, 0, SEEK_CUR); //다음내용 읽기위해 위치를 현재위치로 조정
	fread(&p1.age, sizeof(int), 1, fp); //int 크기만큼 파일로부터 읽어와 p1.age에 작성
	fseek(fp, 0, SEEK_CUR); //다음내용 읽기위해 위치를 현재위치로 조정
	fread(&p1.HP, sizeof(int), 1, fp); //int 크기만큼 파일로부터 읽어와 p1.HP에 작성
	fseek(fp, 0, SEEK_CUR); //다음내용 읽기위해 위치를 현재위치로 조정
	fread(&p1.pos_x, sizeof(double), 1, fp); //double 크기만큼 파일로부터 읽어와 p1.pos_x에 작성
	fseek(fp, 0, SEEK_CUR); //다음내용 읽기위해 위치를 현재위치로 조정
	fread(&p1.pos_y, sizeof(double), 1, fp); //double 크기만큼 파일로부터 읽어와 p1.pos_y에 작성
	fseek(fp, 0, SEEK_CUR); //다음내용 읽기위해 위치를 현재위치로 조정
	fread(&p1.count, sizeof(int), 1, fp); //int 크기만큼 파일로부터 읽어와 p1.count에 작성
	fseek(fp, 0, SEEK_CUR); //다음내용 읽기위해 위치를 현재위치로 조정

	for(int k=0; k<p1.count; k++){ //for구문을 통해 int크기만큼 파일로부터 읽어와 p1.len_friend[k]에 작성
		fread(&p1.len_friend[k], sizeof(int), 1, fp);
		fseek(fp, 0, SEEK_CUR); //다음내용 읽기위해 위치를 현재위치로 조정
	}

	for(int i=0; i<p1.count; i++){ //for구문을 통해 p1.friend[i]크기만큼 파일로부터 읽어와 p1.friend[i]에 작성
		fread(&p1.friend[i], p1.len_friend[i], 1, fp);
		fseek(fp, 0, SEEK_CUR); //다음내용 읽기위해 위치를 현재위치로 조정
	}
	fclose(fp); //파일을 닫음

	//printf함수를 통해 읽어온 내용을 화면에 출력한다
	printf("ID: %s / 나이: %d / HP: %d / 좌표: %.3f, %.3f\n", p1.ID, p1.age, p1.HP, p1.pos_x, p1.pos_y);
	printf("등록된 동맹 수: %d명\n", p1.count);
	for(int i=0; i<p1.count; i++){
		printf("%s ", p1.friend[i]);
		if(i<p1.count-1)
			printf("/ ");
	}
	printf("\n완료되었습니다.\n\n");
}

//메뉴함수
void menu(){ 
	int choice=0; //메뉴번호 받는 변수

	do{
		printf("1. 플레이어 정보 기록\n");
		printf("2. 플레이어 정보 확인\n");
		printf("3. 종료\n");
		printf("입력하세요> ");
		scanf("%d", &choice);

		switch(choice){
			case 1: write_inf(); break;
			case 2: print_inf(); break; 
			case 3: printf("종료되었습니다.\n"); break;
			default: printf("번호를 다시한번 확인해주세요.\n");
		}
	}while(choice!=3); //종료받기전까지 반복

}

int main(int argc, char* argv[]){

	menu(); //메뉴함수 호출

	return 0;
}

