#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct {
	element *data;
	int front, rear, capacity;
}DequeueType;

void InitDequeue(DequeueType *d, int size) { //덱을 초기화 하는 함수
	d->front = d->rear = 0;
	d->capacity = size + 2;		//앞 뒤에서 값을 넣고빼야 하기 때문에 빈 공간이 2칸 필요하다.
	d->data = (element*)malloc(d->capacity * sizeof(element));	//입력받은 크기에서 2칸 큰 capacity크기로 data동적할당
	printf("Size %d Dequeue\n\n", size);
}

int is_full(DequeueType *d) { //덱이 가득 찼으면 1을 반환한다.
	return ((d->rear + 2) % d->capacity == d->front);	//rear에서 모듈러연산 +2 한 값이 front라면 full(두칸만 비어있는 경우)
}

int is_empty(DequeueType *d) { //덱이 비어있으면 1을 반환한다.
	return (d->rear == d->front); //front와 rear값이 같으면 덱이 비어있는 것이다.
}

void print_dequeue(DequeueType *d) { //덱이 가지고 있는 모든 값들을 출력하는 함수
	int data_size, i;	

	data_size = (d->capacity + d->rear - d->front) % d->capacity;
	printf("Q(%d) = ", data_size);
	i = (d->front + 1) % d->capacity;	//front 한칸 앞으로 모듈러 연산후 i에 대입
	while(1) {
		printf("%d ", d->data[i]);	//i번째 덱 값을 출력
		if(d -> rear == i) break; //i가 커지다가 rear위치에 오면 반복탈출
		i = (i + 1) % d->capacity;	//i+1 모듈러 연산
	}
	printf("\n\n");
}

void AddFront(DequeueType *d) {	//AddFront 명령을 받았을 경우 실행
	int item;
	
	if(is_full(d)) { //덱이 가득 찼다면
		printf("Queue is FULL!\n"); //덱이 가득 찼음을 이용자에게 알리고
		print_dequeue(d);	//덱이 가지고 있는 값을 출력
	}else { //덱이 가득 찬 것이 아니라면
		printf("AddFront: "); //이용자에게 덱에 입력할 값을 입력받아 item에 저장
		scanf("%d", &item);
		d->data[d->front] = item; //front위치의 덱이 item을 입력
		d->front = (d->front + d->capacity - 1) % d->capacity; //front - 1 모듈러 연산해서 front값을 한칸 당긴다
		print_dequeue(d);	//방금 입력한 값을 포함해 덱에 입력된 모든 값을 출력
	}
}

void AddRear(DequeueType *d) { //AddRear명령을 받앋을 경우 실행
	int item;
	
	if(is_full(d)) { //덱이 가득 찼다면 가득찼음을 알리고 값을 출력
		printf("Queue is FULL!\n");
		print_dequeue(d);
	} else { //덱이 가득 찬게 아니라면
		printf("AddRear: "); //이용자에게 덱에 입력할 값을 입력받아 item에 저장
		scanf("%d", &item); 
		d->rear = (d->rear + 1) % d->capacity; //rear값을 +1모듈러 연산
		d->data[d->rear] = item; //+1모듈러연산 한 rear위치에 값을 입력
		print_dequeue(d); //방금 입력한 값을 포함해 덱에 입력된 모든 값을 출력
	}
}

void PopFront(DequeueType *d) { //PopFront명령을 받으면 실행
	if(is_empty(d))	printf("Q(0) = Empty\n\n"); //덱이 비어있다면 덱이 비었음을 출력
	else { //덱이 비어있는것이 아니라면
		d->front = (d->front + 1) % d->capacity; //front 를 +1모듈러연산
		printf("PopFront: %d\n", d->data[d->front]); //+1한 front위치의 덱값을 출력
		if(is_empty(d)){ //출력 후 덱이 비었으면 비었다는 상황을 출력
		 	printf("Q(0) = Empty\n\n");
			free(d->data); //덱이 모두 비었으므로 동적할당했던 data를 반환
		}
		else print_dequeue(d); //출력후에도 덱 값이 남아있으면 모든 값을 출력
	}
}

void PopRear(DequeueType *d) { //PopRear 명령을 받으면 실행
	if(is_empty(d)) printf("Q(0) = Empty\n\n"); //덱이 비었으면 덱이 비었음을 출력
	else { //덱이 빈 것이 아니라면
		printf("PopRear: %d\n", d->data[d->rear]); //rear위치의 값을 출력
		d->rear = (d->rear + d->capacity - 1) % d->capacity; //rear를 -1 모듈러 연산한 위치로 이동
		if(is_empty(d)) { //값을 출력 후 덱이 비었다면
			printf("Q(0) = Empty\n\n"); //비었음을 출력
			free(d->data); //값을 모두 빼내었기 때문에 동적할당 되었던 data를 반환
		}
		else print_dequeue(d); //출력후에도 덱 값이 남아있으면 덱값 출력
	}
}

void PrintMenu() { //이용자가 어떤 행동을 할 지 물을때 출력
	printf("1. AddFront\n2. PopFront\n3. AddRear\n4. PopRear\n5. Quit\n");
	printf("입력) ");
}

int main () {
	DequeueType d;
	int size = 0, input = 0, loop = 1;
	printf("Size = ? "); //이용자에게 덱 크기를 묻고 그 값을 size에 대입
	scanf("%d", &size);

	InitDequeue(&d, size); //덱을 초기화
	while(loop) {
		PrintMenu();
		scanf("%d", &input);
		switch(input) {
			case 1: AddFront(&d); break;
			case 2: PopFront(&d); break;
			case 3: AddRear(&d); break;
			case 4: PopRear(&d); break;
			case 5: loop = 0; break;
			default: printf("Wrong input\n");
		}
	}
	return 0;
}
