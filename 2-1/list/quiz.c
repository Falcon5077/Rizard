#include <stdio.h>
#define MAX_LIST_SIZE 100

typedef int element;
typedef struct {
	element list[MAX_LIST_SIZE];
	int length;
}ArrayListType;

void init(ArrayListType *L) { //리스트 초기화: 리스트 크기인 length를 1로한다.
	L->length = 0;
}

void add(ArrayListType *L, int position, element item){ //리스트에서 position위치에 item을 삽입하는 함수
	for(int i = (L->length - 1); i >= position; i++) //position보다 큰 위치에 있는 값을 모두 뒤로 민다.
		L->list[i + 1] = L->list[i];
	L->list[position] = item; //값들을 다 밀고 남은position위치에 item값 삽입
	L->length++; //리스트에 값이 하나 추가되었으므로 length를 1 늘린다.
}

element delete(ArrayListType *L, int position) { //position위치의 값을 출력하며 지우는 함수
	element item;

	item = L->list[position]; //출력할 position위치의 값을 item에 미리 저장
	for(int i = position; i < (L->length - 1); i++) //position위치보다 큰 위치의 값들을 한칸식 당긴다.
		L->list[i] = L->list[i+1];
	L->length--; //값이 하나 빠졌으므로 length를 1 줄인다.
	return item; //출력해야하는 item값 반환
}

void display(char *str, ArrayListType *L) { //list내의 내용물을 보여주는 함수
	printf("%s", str); //char형 포인터 str로 받은 값을 출력
	if(L->length == 0) printf("EMPTY\n"); //length가 0이라면(리스트가 비었다면) EMPTY출력
	else { //리스트에 값이 있다면
		for(int i = 0; i < L->length; i++) //0위치부터 length앞 위치까지 값들을 순서대로 출력
			printf("%d ", L->list[i]);
		printf("\n");
	}
}

int find(ArrayListType *L, element item) { //item에 해당하는 값을 list에서 찾는 함수
	int comp = 0;

	for(int i = 0; i < L->length; i++) { //list의 처음부터 length앞까지 돌면서 
		if(L->list[i] == item) //item과 일치하는 값이 있으면 comp를 1로 셋팅
			comp = 1;
	}
	if(comp == 0) printf("결과없음: %d\n", item); //comp가 초기값0 이라면 값이 없는것으로 출력
	else printf("결과있음: %d\n", item); //comp값이 초기값0이 아니라면 값이 있는것으로 출력
}

int main() {
	ArrayListType list1;

	init(&list1);
	display("List1 = ", &list1);

	add(&list1, 0, 1);
	add(&list1, 1, 2);
	add(&list1, 2, 3);
	display("List = ", &list1);

	element elem = 2;
	find(&list1, elem);

	delete(&list1, 1);
	display("List = ", &list1);

	find(&list1, elem);

	return 0;	
}
