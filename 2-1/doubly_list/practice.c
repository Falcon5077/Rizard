#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ListNode {
	char *name;
	int age;
	struct ListNode *prev;
	struct ListNode *next;
} ListNode;

ListNode *alloc_new_node(char *namevalue, int agevalue) {
	ListNode *node = (ListNode*)malloc(sizeof(ListNode));
	if(namevalue == NULL) {
		node->name = NULL;
		node->age = 0;
		node->prev = node;
		node->next = node;
		return node;
	}
	node->name = (char*)malloc(sizeof(strlen(node->name) + 1));
	strcpy(node->name, namevalue);
	node->age = agevalue;
	return node;
}

ListNode *find_node_name(ListNode *head, char *crit) {
	ListNode *curr = (ListNode*)malloc(sizeof(ListNode));
	for(curr = head->next; curr->next != head; curr = curr->next)
		if(strcmp(curr->name, crit) == 0) return curr;
}

ListNode* find_last_node(ListNode *head) {
	ListNode *last;
	for(last = head->next; last->next != head; last = last->next);
	return last;
}

void insert_last(ListNode *head, char *namevalue, int age) {
	ListNode *node = alloc_new_node(namevalue, age);
	ListNode *last;
	if(head->next == head) {
		head->next = node;
		node->prev = head;
		node->next = head;
		head->prev = node;
		return;
	}
	last = find_last_node(head);
	node->prev = last;
	last->next = node;
	node->next = head;
	head->prev = node;
}

void display(ListNode *head) {
	printf("정방향: ");
	for(ListNode *curr = head->next; curr != head; curr = curr->next)
		printf("%s(%d) -> ", curr->name, curr->age);
	printf("\b\b\b  \n역방향: ");
	for(ListNode *curr = head->prev; curr != head; curr = curr->prev)
		printf("%s(%d) -> ", curr->name, curr->age);
	printf("\b\b\b  \n");
}	

int main() {
	ListNode *head = alloc_new_node(NULL, 0);

	insert_last(head, "홍길동", 12);
	insert_last(head, "전주성", 13);
	insert_last(head, "고멘네", 48);

	display(head);

	return 0;
}

