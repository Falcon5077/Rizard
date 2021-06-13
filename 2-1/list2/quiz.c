#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct ListNode {
	int age;
	char *name;
	struct ListNode *next;
} ListNode;
int count = 1;

ListNode *add_new_node(char *namevalue, int agevalue) { //새로운 노드 추가할당 하는 함수
	ListNode *node = (ListNode*)malloc(sizeof(ListNode));
	if(namevalue == NULL) { //namevalue값에 NULL이 들어올 경우 (main함수에서 head값 초기화 할 때
		node->name = NULL;
		node->age = 0;
		node->next = NULL;
		return node;
	} //head값 초기화 하는 경우가 아닐 때
	node->name = (char*)malloc(sizeof(strlen(namevalue) + 1)); 
	//node->name이 포인터로 선언되었으므로 동적으로 namevalue만큼 크기를 할당해준다.
	strcpy(node->name, namevalue); //node->name에 namevalue값을 집어넣는다.
	node->age = agevalue;	//node->age에 agevalue값을 넣는다.
	node->next = NULL; 		//node->next에는 NULL값을 넣는다.
	return node;
}

ListNode *find_by_name(ListNode *head, char *namevalue) { //입력받은 namevalue값이 들어있는 node를 찾는다.
	ListNode *curr; //찾은값을 대입할 노드 할당
	for(curr = head->next; curr != NULL; curr = curr->next) { //curr노드를 마지막위치까지 반복
		if(strcmp(curr->name, namevalue) == 0) //for문이 돌며 현재위치 curr->name에 namevalue값이 있으면 curr반환
			return curr;
		count++; //몇 번 반복했는지 센다.
	}
	return NULL; //curr가 끝까지 돌았을 때 까지 값이 없으면 반환
}

void insertFirst(ListNode *head, char* namevalue, int agevalue) { //가장 첫위치에 node값을 위치시키는 함수
	ListNode *node = add_new_node(namevalue, agevalue); //add_new_node함수로 노드를 할당해서
	head->next = node; //그 노드를 head->next위치에 넣는다.
}

//criteria값을 기준으로 앞 위치에 namevalue가 들어있는 노드를 할당해서 위치시킨다.
void insertBefore(ListNode *head, char* criteria, char* namevalue, int agevalue) {
	ListNode *node = add_new_node(namevalue, agevalue); //node이름으로 새 노드를 할당한다.
	ListNode *crit = find_by_name(head, criteria); //crit에 criteria노드의 위치를 할당한다.
	ListNode *pre; //node앞 위치를 찾기위한 pre노드
	if(crit == NULL) { //criteria값이 든 노드를 찾지 못했다면 바로 반환
		printf("%s는 존재하지 않습니다!before\n", criteria);
		return;
	}
	if(count == 1) { //find_by_name 함수가 count 1로 종료되었을 경우 (crit위치가 head=>next위치이다)
		head->next = node; //head->next위치에 노드를 할당한다
		node->next = crit; //node->next위치에 crit(criteria)노드를 위치시킨다.
	}
	if(count > 1) { //find_by_name함수가 count 1 보다 큰 값으로 종료되었을 경우 (crit위치가 가장 처음이 아니다)
		for(pre = head->next; pre->next != crit; pre = pre->next); 
		//pre->next위치가 node일때까지 반복한다. (node앞위치까지)
		pre->next = node; //crit앞에서 뒤에 node를 위치시킨다.
		node->next = crit; //node->next위치에 crit을 위치시킨다.
		count = 1;
	}
}

//crit기준으로 뒤의 위치에 namevalue가 들어있는 노드를 위치시킨다.
void insertNext(ListNode *head, char *criteria, char *namevalue, int agevalue) { 
	ListNode *node = add_new_node(namevalue, agevalue); //node새로운 노드를 할당
	ListNode *crit = find_by_name(head, criteria); //criteria이름이 있는 노드위치를 찾아 crit에 반환
	ListNode *behind; //뒤의 위치를 할당받을 behind노드 할당
	if(crit == NULL) { //crit이 criteria가 든 노드를 찾지 못하면 못찾았다는 내용 반환
		printf("%s는 존재하지 않습니다!Next\n", criteria);
		count = 1;
		return;
	} //criteria위치값을 찾았다면
	count = 1;
	if(crit->next == NULL) //crit뒤에 아무값도 없다면
		crit->next = node; //crit의 다음위치에 node를 위치시킨다.
	else { //crit뒤에도 노드가 존재한다면
		behind = crit->next;
		crit->next = node;
		node->next = behind; //node뒤에도 crit뒤에 있던 값을 할당한다.
	}
}

void display(char *list, ListNode *head) { //list가지고 있는 값을 모두 출력
	printf("%s() -> %s",__func__, list);
	if(head->next == NULL){ //head->next가 NULL이면 아무값도 없는것
		printf("EMPTY\n");
		return;
	} //값이 있다면
	for(ListNode *node = head->next; node != NULL; node = node->next) //node가 NULL일때 까지 head->next부터 계속 진행
		printf("%s(%d세), ", node->name, node->age); //for문이 돌며 그 위치의 node안의 value값들을 출력
	printf("\b\b \n"); //마지막 위치 콤마 지워주기 위함
}

void getAge(ListNode *head, char *namevalue) { //namevalue가 있는 노드의 age값을 구하는 함수
	printf("%s() -> ", __func__);
	ListNode *curr = find_by_name(head, namevalue); //curr 에 namevalue가 위치한 노드 주소값을 반환
	if(curr == NULL) { //못찾으면 못찾았다고 출력
		printf("%s은 리스트에 없습니다.\n", namevalue);
		count = 1;
		return;
	}
	count = 1;
	printf("%s의 나이는 %d세\n", curr->name, curr->age); //찾았으면 찾은위치 age값 출력
}

void delete(ListNode *head, char *namevalue) { //namevalue가 위치한 노드 지우는 함수
	printf("%s() -> ", __func__);
	ListNode *curr = find_by_name(head, namevalue); //curr에 namevalue가 위치한 노드 주소값을 반환
	ListNode *pre; //curr 앞 위치 주소값을 넣을 pre노드 
	if(curr == NULL) {
		printf("%s은 리스트에 없습니다.\n", namevalue);
		count = 1;
		return;
	}
	if(count == 1) { //찾는 위치가 젤 첫노드일때
		if(curr->next == NULL) { //현재 남은 노드가 이 노드 뿐일때
			head->next == NULL; //head->next = NULL로 초기화 하고 끝
			free(curr);
			return;
		} //현재 노드 뒤에도 다른 노드가 있을때
		head->next = curr->next; //head->next를 curr->next로 줘서 curr 노드를 건너 뛰고 curr을 반환한다
		free(curr);
		return;
	}//찾는위치가 첫노드도 아니고 뒤에 값도 있을때
	for(pre = head; pre->next != curr; pre = pre->next); //curr 앞 위치의 노드를 찾는다 = pre
	pre->next = curr->next; //pre->next에 curr->next값을 넣어서 curr노드를 없앤다
	free(curr); //curr노드 free
	printf("%s이 삭제되었습니다.\n", namevalue);
}

int main() {
	
	ListNode *head = add_new_node(NULL, 0);

	display("List = ", head);

	insertFirst(head, "홍길동", 30);
	insertBefore(head, "홍길동", "김길동", 20);
	insertNext(head, "홍길동", "최길동", 15);
	display("List = ", head);
	getAge(head, "홍길동");

	delete(head, "홍길동");
	display("List = ", head);

	delete(head, "김길동");
	display("List = ", head);

	delete(head, "최길동");
	display("List = ", head);
	
	delete(head, "홍길동");
	display("List = ", head);

	return 0;
}
