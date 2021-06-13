#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct {
	element *data;
	int front, rear, capacity;
}QueueType;

void InitQueue(QueueType *s, int size) {
	printf("Size %d Queue.\n\n", size);
	s->front = s->rear = 0;
	s->capacity = size + 1;
	s->data = (element*)malloc(s->capacity * sizeof(element));
}

int is_full(QueueType *s) { //rear가 front 바로뒤에 있다면 큐는 가득찬것
	return ((s->rear +1) % s->capacity == s->front);
}

int is_empty(QueueType *s) { //rear와 front가 같은 위치에 있다면 큐는 빈것
	return (s->front == s->rear);
}

void Enqueue(QueueType *s) { //이용자로부터 Enqueue명령어를 받았을 경우 실행되는 함수
	int item = 0;
	int itemsize = 0;
	
	if(is_full(s)) { 	//큐에 값을 넣으려고 하는데 가득 찼다면?
		itemsize = (s->capacity + s->rear - s->front) % s->capacity; //itemsize에 현재 큐에 저장된 데이터 양을 저장
		printf("Queue is Full!!\n");  //큐가 가득찼다는 경고문 출력
		printf("Q(%d) = ", itemsize); //Q(아이템사이즈) = 
		for(int i = (s->front + 1) % s->capacity; i <= s->rear;) {	//i에 front 다음값을 넣고, rear보다 작거나 같을동안 반복
			printf("%d ", s->data[i]);
			i = (i + 1) % s->capacity; //원형큐 이므로 단지++되는것이 아니라 모듈러연산을 통해 큐의 마지막위치 다음 0위치로 가도록 설정
			if(i == s->front) break; // i값이 front값과 같아지면 반복문 탈출 (그렇지 않으면 무한반복에 빠진다)
		}
		printf("\n\n");
	}
	else { //큐가 가득차지 않았을 경우
		printf("Enqueue: "); //넣을 값을 입력받아item에 저장
		scanf("%d", &item);
		s->rear = (s->rear + 1) % s->capacity;	//모듈러연산을 통해 다음위치의 배열에 값을 저장
		s->data[s->rear] = item;
		itemsize = (s->capacity + s->rear - s->front) % s->capacity; //itemsize에 현재큐에 저장된 데이터 양을 저장
		printf("Q(%d) = ", itemsize);	//Q(데이터양) = 
		for(int i = (s->front + 1) % s->capacity; i <= s->rear;) {	//i에 front다음값을 넣고, rear보다 작거나 같을동안 반복
			printf("%d ", s->data[i]);
			i = (i + 1) % s->capacity; //모듈러 연산을 통해 원형 큐 구현
			if(i == s->front) break;
		}
		printf("\n\n");
	}
}

void Dequeue(QueueType *s) { //이용자가 Dequeue를 요청했을 경우 실행되는 함수
	int item = 0;
	int itemsize = 0;

	if(is_empty(s)) {	//큐가 비어있다면?
		printf("Q(0) = Empty\n\n");	//큐에 값이 없고 비어있음을 출력
	}
	else {	//큐가 비어있는게 아니라면
		s->front = (s->front + 1) % s->capacity; //모듈러 연산을 통해 front를 한칸 앞으로 이동후 값을 출력
		item = s->data[s->front];
		printf("Dequeued: %d\n", item);
		if(is_empty(s)) { //값을 빼낸 후 큐가 비었다면 큐에 값이 없고 비어있음을 출력
			printf("Q(0) = Empty\n\n"); 
			free(s->data); //값을 모두 빼내었으므로 동적으로 할당했던 data를 반환한다.
		}
		else { //값을 하나 빼낸 후에도 큐가 비어있지 않다면
			itemsize = (s->capacity + s->rear - s->front) % s->capacity; //itemsize에 큐에 든 데이터 크기를 저장
			printf("Q(%d) = ", itemsize);	//Q(큐데이터 크기) = 
			for(int i = (s->front + 1) % s->capacity; i <= s->rear;) {	//i에 front다음값을 해서 rear값보다 작거나 같을동안 반복
				printf("%d ", s->data[i]);	//i번째 큐값을 반환하며 출력
				i = (i + 1) % s->capacity;	//모듈러 연산을 통해 원형 큐 구현
				if(i == (s->rear + 1) % s->capacity) break; // i값이 rear+1 위치값과 같으면 반복탈출(front+1 ~ rear 까지의 값을 출력해야 하기 때문)
			}
			printf("\n\n");
		}
	}
}

void PrintMenu() {
	printf("1. Enqueue\n2. Dequeue\n3. Quit\n입력)");
}

int main() {
	QueueType s;
	int size = 0, input = 0, loop = 1;
	printf("SIZE = ? ");
	scanf("%d", &size);

	InitQueue(&s, size);
	while(loop) {
		PrintMenu();
		scanf("%d", &input);
		switch(input) {
			case 1: Enqueue(&s); break;
			case 2: Dequeue(&s); break;
			case 3: loop = 0; break;
			default: printf("Wrong input..\n");
		}
	}
	return 0;
}
