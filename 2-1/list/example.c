#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
	int age;
	char *name;
	struct ListNode *next;
} ListNode;
int count = 1;

void init(ListNode **head) {	//노드 초기화 함수
	*head = (ListNode*)malloc(sizeof(ListNode)); //head를 받아 초기화 하고 노드를 하나 만들어서 할당한다.
	(**head).age = 0;
	(*head)->name = NULL;
	(*head)->next = NULL;
}

void display(const char* listname, ListNode *head) {	//리스트가 가지고 있는 값 출력
	printf("%s() -> ",__func__); //__func__을 이용해서 현재 함수 이름을 출력
	if(head->next == NULL) { //head값이 가르키는 위치가 NULL상태라면 리스트는 비어있는것이다
		printf("%sEMPTY\n", listname);
		return;
	}
	//head->next의 첫번째 위치부터 한칸씩 next로 for문 돌면서 모든 노드를 탐색한다.
	for(ListNode *curr = head->next; curr != NULL; curr = curr->next)
		printf("%s(%d세) -> ", curr->name, curr->age); //탐색한 현재노트의 value값들을 출력
	printf("\b\b\b  \n");//제일 마지막 위치에서 ,(콤마)를 지우기 위함
}

void insert_last(ListNode *new_node, ListNode *head) { //노드들 마지막 위치에 입력받은 값을 삽입하는 함수
	ListNode *curr; //curr이름의 노드를 생성한다.
	//curr노드에 head 주소값을 넣어주고, curr->next가 NULL일때 까지 즉, curr노드가 마지막 노드가 될때까지 반복
	for(curr = head; curr->next != NULL; curr = curr->next); 
	curr->next = new_node; //마지막노드인 curr노드 다음노드에 new_node를 입력
}

ListNode* alloc_new_node(const char *namevalue, int agevalue) { //새로운 노드를 생성하는 함수
	ListNode *node = (ListNode*)malloc(sizeof(ListNode)); //node이름으로 노드하나 만들고 ListNode로 크기를 할당
	node->name = (char*)malloc(sizeof(strlen(namevalue) + 1)); //name위치에 이름값을 받을 크기를 동적할당받는다
	strcpy(node->name, namevalue); //node->name에 입력받은 이름을 strcpy함수를 이용, 복사한다.
	node->age = agevalue;	//age를 입력
	node->next = NULL;		//새로 만든 노드의 다음값은 NULL이다 

	return node; //값들을 다 할당하고 저장한다음 그 노드를 반환한다.
}

void insert(const char *namevalue, int agevalue, ListNode *head) {
	ListNode *node = alloc_new_node(namevalue, agevalue); //새로운 노드를 하나 만들어서 이름과 나이값을 저장한다.
	
	insert_last(node, head); //방금 생성한 노드를 마지막 위치에 얹어놓기
}

ListNode* find_curr_node(const char *namevalue, ListNode *head) {			//namevalue값과 일치하는 노드의 위치를 구하는 함수
	for(ListNode *curr = head->next; curr != NULL; curr = curr->next) { //노드 첫부터 끝까지 탐색
		if(strcmp(curr->name, namevalue) == 0)			//탐색 중 namevalue값과 일치하는 값을 가진 노드 찾을시 그 노드값 반환
			return curr;
		count++; //탐색할 때 마다 카운트 해서 기록한다.
	}
	count = 1;
	return NULL; //찾는 값이 없으면 NULL값을 반환한다.
}

void getAge(const char *namevalue, ListNode *head) { //namevalue와 일치하는 이름을 가진 사람의 나이를 출력
	ListNode *node = find_curr_node(namevalue, head); //namevalue와 일치하는 값이 있는 노드위치를 가져온다.
	if(node == NULL) { //NULL이 반환되면 값이 없는것이므로 
		printf("%s는 존재하지 않습니다.\n", namevalue);
		return;
	}
	printf("%s의 나이는 %d세 입니다.\n", namevalue, node->age); //일치하는 노드가 있을경우 해당노드 값을 출력
	count = 1;
}

void delete(const char *namevalue, ListNode *head) { //namevalue와 일치하는 값이 있는 노드를 삭제
	ListNode *node = find_curr_node(namevalue, head); //namevalue와 일치하는 값이 있는 노드를 찾음
	ListNode *pre;
	if(node == NULL) { //일치하는 노드가 없을경우 존재하지 않음을 출력 
		printf("%s는 존재하지 않습니다.\n", namevalue);
		return;
	}
	// 일치하는 값이 있는 경우
	if(count == 1) { //일치하는 노드 위치가 첫번째일 경우
		head->next = node->next; //head->next가 node->next로 주소값을 변경해서 node위치 값을 바로 삭제
		free(node);
	}else { //일치하는 노드 위치가 두번째 이상일 경우
		for(pre = head->next; pre->next != node; pre = pre->next); //pre이름의 노드를 pre->next가 node가 될때까지 반복
		pre->next = node->next; //pre->next값이 node->next값이 되게 셋팅하며 node노드를 삭제
		free(node);
	}
	
	printf("%s가 삭제되었습니다.\n", namevalue);	
}

int main(int argc, char* argv[]) {
	
	ListNode *head = NULL;
	
	init(&head);

	display("리스트 = ", head);

	insert("홍길동", 20, head);
	insert("김길동", 30, head);
	insert("최길동", 15, head);
	display("List = ", head);

	getAge("홍길동", head);
	
	delete("홍길동", head);
	display("List = ", head);
	getAge("홍길동", head);
	getAge("최길동", head);

	return 0;
}
