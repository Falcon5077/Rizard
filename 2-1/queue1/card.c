#include <stdio.h>
#define MAX_SIZE 1000

typedef struct {
	int Deck[MAX_SIZE];
	int rear, front;
}Qtype;

void init_queue(Qtype *q) {
	q->rear = q->front = 0;
}

int dequeue(Qtype *q) {
	q->front = (q->front + 1) % MAX_SIZE;
	return q->Deck[q->front];
}

void enqueue(Qtype *q, int item) {
	q->rear = (q->rear + 1) % MAX_SIZE;
	q->Deck[q->rear] = item;
}

void make_deck(Qtype *q, int count) {
	for(int i = 1; i<=count; i++)
		enqueue(q, i);
}

void shake_deck(Qtype *q) {
	int temp = 0;
	int count = 0;
	scanf("%d", &count);

	make_deck(q, count);
	for(int i = 1; i<count; i++) {
		printf("%d ", dequeue(q));
		temp = dequeue(q);
		enqueue(q,  temp);
	}
	printf("%d", dequeue(q));
	
}

int main() {
	Qtype q;
	init_queue(&q);
	shake_deck(&q);
	return 0;
}
