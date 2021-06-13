#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
	int age;
	char *name;
	struct ListNode *next;
} ListNode;
int count = 1;

void init(ListNode **head) {
	*head = (ListNode*)malloc(sizeof(ListNode));
	(*head)->age = 0;
	(*head)->name = NULL;
	(*head)->next = NULL;
}

void display(char *listname, ListNode *head) {
	printf("%s()-> %s",__func__, listname);
	if(head->next == NULL) {
		printf("EMPTY\n");
		return;
	}
	for(ListNode *curr = head->next; curr != NULL; curr = curr->next)
	  printf("%s(%d세), ", curr->name, curr->age);
	printf("\b\b \n");
}

ListNode* alloc_new_node(char *namevalue, int agevalue) {
	ListNode *node = (ListNode*)malloc(sizeof(ListNode));
	node->name = (char*)malloc(sizeof(strlen(namevalue) + 1));
	node->age = agevalue;
	strcpy(node->name, namevalue);
	node->next = NULL;

	return node;
}

void insert_last(ListNode *head, ListNode *node) {
	ListNode *curr;	
	for(curr = head; curr->next != NULL; curr = curr->next);
	curr->next = node;
} 

void insert(ListNode *head, char *namevalue, int agevalue) {
	ListNode *node = alloc_new_node(namevalue, agevalue);
	
	insert_last(head, node);
}

ListNode* find_by_name(ListNode *head, char *namevalue) {
	for(ListNode *curr = head->next; curr != NULL; curr = curr->next) {
		if(strcmp(curr->name, namevalue) == 0) return curr;
		count++;
	}
	return NULL;
}

void getAge(ListNode *head, char *namevalue) {
	ListNode *node = find_by_name(head, namevalue);
	if(node == NULL){
		printf("%s은 현재 리스트에 없습니다.\n", namevalue);
		count = 1;
		return;
	}
	printf("%s의 나이는 %d세\n", namevalue, node->age);
	count = 1;
}

void delete(ListNode *head, char* namevalue) {
	ListNode *curr = find_by_name(head, namevalue);
	ListNode *pre;
	if(curr == NULL) {
		printf("%s은 현재 리스트에 없습니다.\n", namevalue);
		return;
	}
	if(count == 1) {
		head->next = curr->next;
		free(curr);
	}else {
		for(pre = head; pre->next != curr; pre = pre->next);
		pre->next = curr->next;
		count = 1;
	}
	printf("삭제를 완료했습니다.\n");
}

int main() {
	
  ListNode *head = NULL;

  init(&head);

  display("리스트= ", head);

  insert(head, "홍길동", 20);
  insert(head, "김길동", 30);
  insert(head, "최길동", 15);
  display("List= ", head);	

  getAge(head, "홍길동");

  delete(head, "홍길동");
  display("List = ", head);
  getAge(head, "홍길동");
  getAge(head, "최길동");

  return 0;
}
