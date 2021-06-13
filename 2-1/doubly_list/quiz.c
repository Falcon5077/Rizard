#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode{ //리스트 구조체 선언
	char *name;
	int age;
	struct ListNode *next;
	struct ListNode *prev; //이번에는 뒤로 가는 포인터도 필요하므로 prev도 선언함
} ListNode;

ListNode *init() { //head 초기화 함수->이중연결리스트 이므로 아무것도 없는 상태일때 head는 자기자신을 가리킨다.
	ListNode *node = (ListNode*)malloc(sizeof(ListNode));
	node->name = NULL;
	node->age = 0;
	node->next = node;
	node->prev = node;
	return node;
}

ListNode *add_new_node(char *namevalue, int agevalue) { //새로운 노드를 추가하는 함수
	ListNode *node = (ListNode*)malloc(sizeof(ListNode)); //새로운 노드를 하나 할당한다
	node->name = (char*)malloc(sizeof(strlen(namevalue) + 1)); //할당한 노드의 name위치에 namevalue만큼의 크기를 할당한다.
	strcpy(node->name, namevalue); //동적할당된 name위치에 namevalue값 삽입 
	node->age = agevalue; //age위치에 agevalue값 삽입
	return node; //값들이 모두 저장된 노드를 반환한다.
}

ListNode *find_last_node(ListNode *head) { //List에서 가장 마지막 위치의 노드를 찾는다.
	ListNode *last;
	//for문이 돌며 last->next 가 head인 위치까지 반복한다(젤 마지막노드 next값은 head이기 때문)
	for(last = head->next; last->next != head; last = last->next);
	return last; //찾은 노드 주소값을 반환한다.
}

void insert_last(ListNode *head, char *namevalue, int agevalue) { //리스트의 마지막 위치 뒤에 값을 입력한다.
	ListNode *node = add_new_node(namevalue, agevalue); //노드를 하나 할당하여 add_new_node로 값을 저장한다.
	if(head->next == head) { //head->next가 head인 경우: 아직 리스트에 아무 값도 할당되지 않은 경우
		head->next = node; //head바로 뒤로 값을 저장하도록 포인터를 조정한다.
		node->next = head;
		head->prev = node;
		node->prev = head;
		return;
	} //head->next에 값이 있을때 -> 리스트에 최소 한개의 값이 있다.
	ListNode *last = find_last_node(head); //노드를 하나 할당해 find_last_node함수로 찾은 주소값을 대입한다.
	last->next = node; //포인터를 순서대로 조정해 젤 마지막 위치의 다음위치에 노드를 위치시킨다
	node->prev = last;
	node->next = head;
	head->prev = node;
}

void Set(ListNode *head) { //퀴즈예문에서 이야기했던 김, 홍, 최 값들을 순서대로 마지막 위치에 set시키는 함수이다.
	insert_last(head, "김", 20);
	insert_last(head, "홍", 30);
	insert_last(head, "최", 15);

	printf("%s() worked.\n\n",__func__);
}

void Delete_last(ListNode *head) { //리스트의 마지막 위치에 있는 값들을 삭제하는 함수이다.
	if(head->next == head) { //head->next값이 head를 가리키는 경우 -> 리스트에 들어있는 값이 없다.
		printf("삭제 실패 -> 데이터 없음\n\n");
		return;
	} //리스트에 들어있는 값이 있을경우
	ListNode *last = find_last_node(head); //리스트의 가장 마지막 위치를 찾는다.
	ListNode *before = last->prev; //마지막위치의 prev의 값을 berfore에 대입한다.
	if(head->next == last) { //리스트에 있는 노드가 하나밖에 없을 경우
		printf("%s(%d) 삭제됨\n\n", last->name, last->age);
		head->next = head; //head뒤에 있는 값을 바로 삭제시킨다.
		head->prev = head;
		free(last);
		return;
	} //리스트에 있는 노드개수가 2개이상인 경우
	printf("%s(%d) 삭제됨\n", last->name, last->age);
	before->next = head; //before뒤의 값을 삭제시키는 식으로 포인터를 조정한다.
	head->prev = before;
	free(last);
}

void Display_ordered(ListNode *head) { //순서대로 리스트의 값들을 출력한다.
	if(head->next == head) { //head->next가 head를 가리키는경우 값이 없다.
		printf("List = EMPTY\n\n");
		return;
	} //리스트에 값이 존재할 경우
	printf("List = ");
	for(ListNode *curr = head->next; curr != head; curr = curr->next) //curr노드를 head->next에서 head가 나올때까지 반복하며 값들을 뱉어낸다.
		printf("%s(%d), ", curr->name, curr->age);
	printf("\b\b \n\n");
}	

void Display_reversed(ListNode *head) { //반대로 리스트의 값들을 출력한다.
	if(head->next == head) { //리스트가 비어있을 경우 위 함수와 동일하게 EMPTY출력
		printf("List = EMPTY\n\n");
		return;
	}
	printf("List = ");
	for(ListNode *curr = head->prev; curr != head; curr = curr->prev) //head->prev위치부터 prev를 타고 반대로 for문을 타며 값들을 뱉어낸다
		printf("%s(%d), ", curr->name, curr->age);
	printf("\b\b \n\n");
}

void PrintMenu() { //이용자가 값을 입력하기 위해 필요한 메뉴판
	printf("----------\n");
	printf("1. Set()\n2. Display_ordered()\n3. Display_reversed()\n");
	printf("4. Delete_last()\n5. Exit()\n");
	printf("----------\n? ");
}

int main() {
	int order = 0, loop = 1;
	
	ListNode *head = init(); //head를 선언해주고 init함수로 초기화 해준다.
	
	while(loop) {
		PrintMenu();
		scanf(" %d", &order);
		switch(order) {
			case 1: Set(head); break;
			case 2: Display_ordered(head); break;
			case 3: Display_reversed(head); break;
			case 4: Delete_last(head); break;
			case 5: loop = 0; break;
			default: printf("잘못 입력했습니다\n"); break;
		}
	}

	return 0;
}
