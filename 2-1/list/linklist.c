#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
	int age;
	char name[20];
	struct ListNode *next;
}ListNode;
int size = 0;

void display(char *list, ListNode *head) {
	printf("%s() -> ", __func__);
	if(head == NULL) printf("%sEMPTY\n", list);
	else if(head->next == NULL) printf("%sEMPTY\n", list);
	else {
		printf("%s", list);
		for(ListNode *p = head; p != NULL; p = p->next)
			printf("%s(%d세), ", p->name, p->age);
		printf("\b\b \n");
	}
}

ListNode* insert(ListNode *head, char *namevalue, int agevalue) {
	ListNode *p = (ListNode*)malloc(sizeof(ListNode));
	ListNode *pre;

	strcpy(p->name, namevalue);
	p->age = agevalue;
	if(head == NULL) {
		p->next = head;
		head = p;
		size++;
		return head;
	}else {
		pre = head;
		for(int i = 0; i < size - 1; i++)
			pre = pre->next;
		pre->next = p;
		p->next = NULL;
		size++;
		return head;
	}
}

ListNode* delete(ListNode *head, char* namevalue) {
	int count = 1;
	printf("%s() -> ",__func__);
	ListNode *pre;
	for(ListNode *p = head; p != NULL; p = p->next) {
		if(strcmp(p->name, namevalue) == 0) {
			if(count == 1) {
				p = head;
				head = p->next;
				free(p);
				size--;
				printf("%s이 삭제되었습니다.\n", namevalue);
				return head;
			} else{
				pre = head;
				for(int i = 0; i < count - 2; i++)
					pre = pre->next;
				pre->next = p->next;
				free(p);
				size--;
				printf("%s이 삭제되었습니다.\n", namevalue);
				return head;
			}
		}
		count++;
	}
}

void getAge(ListNode *head, char *namevalue) {
	int confirm = 0;
	printf("%s() -> ",__func__);
	for(ListNode *p = head; p != NULL; p = p->next) {
		if(strcmp(p->name, namevalue) == 0) {
			printf("%s의 나이는 %d세\n", p->name, p->age);
			confirm = 1;
		}
	} if(confirm != 1) printf("%s은 현재 리스트에 없습니다.\n", namevalue);
}

int main() {
	ListNode *head = NULL;

	display("리스트= ", head);

	head = insert(head, "홍길동", 20);
	head = insert(head, "김길동", 30);
	head = insert(head, "최길동", 15);
	display("List = ", head);

	getAge(head, "홍길동");

	head = delete(head, "홍길동");
	display("List = ", head);
	getAge(head, "홍길동");
	getAge(head, "최길동");

	return 0;
}
