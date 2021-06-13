#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode{
	int age;
	char *name;
	struct LintNode *next;
}ListNode;
int size = 0;

void init(ListNode *head) {
	head->name = (char*)malloc(5 * sizeof(char));
}

void display(char *list, ListNode *head) {
	printf("%s() -> ",__func__);
	if(head == NULL) printf("리스트 = EMPTY");
	else {
		printf("%s", list);
		for(ListNode *p = head; p != NULL; p = p->next) {
			printf("%s", p->name);
			printf("(%d세), ", p->age);
		}
	}
}

ListNode* insert(ListNode *head, char *value, int curage) {
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	ListNode *pre;
	p->age = curage;
	p->name = value;

	if(head != NULL) {
		pre = head;
		for(int i = 0; i < size - 1; i++)
			pre = pre->next;
		pre->next = p;
	}else {
		p->next = head;
		head = p;
	}
}

ListNode* delete(ListNode *head, char *value) {
	int count;
	ListNode *removed;
	ListNode *pre;

	for(ListNode *p = head; p != NULL; p = p->next) {
		if(strcmp(p->name, value) == 0) {
			if(count == 0) {
				removed = head;
				head = removed->next;
				free(removed);
			}else {
				pre = head;
				for(int i = 0; i < count - 1; i++)
					pre = pre->next;
				removed = pre->next;
				pre->next = removed->next;
				free(removed);
			}
		}
		count++;
	}
}

void getAge(ListNode *head, char *value) {
	int comp = 0;
	for(ListNode *p = head; p != NULL; p = p->next) {
		if(strcmp(p->name, value) == 0) {
			printf("%s의 나이는 %d세\n", p->name, p->age);
			comp = 1;
		}
	} if(comp != 1) printf("%s은 현재 리스트에 없습니다.\n", value);
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
