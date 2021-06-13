#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NUM 10000

typedef int element;
typedef struct {
	element data[MAX_NUM];
	int front, rear;
}	QueueType;

void init_queue(QueueType *q) {		//queue초기화 및 동적할당
	q->front = q -> rear = 0;
}

int is_empty(QueueType *q) {
	return(q->front == q->rear);
}	

int is_full(QueueType *q) {	//rear값을1더하고 queue크기를 나눈값의 나머지가 front와 같으면 포화
	return((q->rear + 1) % MAX_NUM == q->front);
}

void enqueue(QueueType *q, element item) {
	q->rear = (q->rear + 1) % MAX_NUM;
	q->data[q->rear] = item;
}

void dequeue(QueueType *q) {
	if(is_empty(q)){ 
		printf("-1\n");
	} else {
		q->front = (q->front + 1) % MAX_NUM;
		printf("%d\n", q->data[q->front]);
	}
}

void peek_front(QueueType *q) {
	if(is_empty(q)) {
		printf("-1\n");
	} else {
		printf("%d\n", q->data[(q->front+1) % MAX_NUM]);
	}
}

void peek_rear(QueueType *q) {
	if(is_empty(q)) {
		printf("-1\n");
	} else {
		printf("%d\n", q->data[q->rear]);
	}
}

int size_of_queue(QueueType *q) {
	return (MAX_NUM + q->rear - q -> front) % MAX_NUM; 
}

void input(QueueType *q){ 
	int count, item;
	char order[10];

	scanf("%d", &count);
	for(int i = 0; i < count; i++) {
		scanf("%s", order);

		if(strcmp(order, "push") == 0) {
			scanf("%d", &item);
			enqueue(q, item);
		}else	if (strcmp(order, "pop") == 0) dequeue(q);
		else if (strcmp(order, "size") == 0) printf("%d\n", size_of_queue(q));
		else if (strcmp(order, "empty") == 0) printf("%d\n", is_empty(q));
		else if (strcmp(order, "front") == 0) peek_front(q);
		else if (strcmp(order, "back") == 0) peek_rear(q);
	}
}

int main() {
	QueueType queue;

	init_queue(&queue);
	input(&queue);

	return 0;
}







