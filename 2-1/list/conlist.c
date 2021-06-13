#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct Node {
	element data;
	struct Node *link;
}Node;
int size = 0;

void print_list(Node *head) {
	printf("List(%d) = ", size);
	for(Node *p = head; p != NULL; p = p->link)
		printf("%d -> ", p->data);
	printf("NULL\n\n");
}

Node* insert_first(Node *head) {
	int value;
	printf("값을 입력> ");
	scanf(" %d", &value);

	Node *p = (Node*)malloc(sizeof(Node));
	p->data = value;
	p->link = head;
	head = p;
	size++;
	return head;
}

Node* insert(Node *head) {
	Node *pre;
	Node *p = (Node*)malloc(sizeof(Node));
	int value, position;
	printf("값을 입력> ");
	scanf(" %d", &value);
	printf("넣고싶은 위치> ");
	scanf(" %d", &position);

	pre = head;
	for(int i = 0; i < position - 2; i++) {
		pre = pre->link;
	}
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	size++;
	return head;
}

Node* delete_first(Node* head) {
	Node *removed;
	if(head == NULL) return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	size--;
	return head;
}

Node* delete(Node *head) {
	Node *removed;
	Node *pre;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	return head;
}

Node* delete_all(Node *head) {
	if(head == NULL) return NULL;
	while (head != NULL) {
		Node *removed;
		removed = head;
		head = removed->link;
		free(removed);
		size--;
	}
	printf("모든 값이 삭제되었습니다.\n");
	return head;
}

void PrintMenu() {
	printf("1. 앞쪽 입력\n2. 일반입력\n3. 앞쪽 지우기\n4. 일반지우기\n5. 모두지우기\n6. 종료\n");	
	printf("입력하세요> ");
}

int main () {
	int order = 0, loop = 1;
	Node *head = NULL;

	while(loop) {
		PrintMenu();
		scanf("%d", &order);
		switch(order) {
			case 1: head = insert_first(head); break;
			case 2: head = insert(head); break;
			case 3: head = delete_first(head); break;
			case 4: head = delete(head); break;
			case 5: head = delete_all(head); break;
			case 6: loop = 0; break;
		}
		print_list(head);
	}
	return 0;
}
