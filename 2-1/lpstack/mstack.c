#include <stdio.h>
#include <stdlib.h>

typedef int element;
int top = -1;				//stack을 구현하는데 필요한 top을 전역함수로 뺀 후 -1로 초기화
int capacity = 1;		//동적메모리 할당을 위한 크기를 결정해주는 변수
int init = 0;				//stack이 동적으로 초기화된 적이 있는지 가르쳐주는 변수
typedef struct {
	element *stack;
	}	StackType;

void PushStack(StackType *s) {
	int tmp = 0;
	printf("Push: ");
	scanf("%d", &tmp);

	if(init == 0)	{		//init이 0이라면stack이 초기화 된 적이 없는 것이므로 capacity크기로 초기화 해 준다.
		s->stack = (element*)malloc(capacity*sizeof(element));
		init++;	//초기화 되었으니 init은 1을 나타내게 된다.
	}

	if(top+1 >= capacity)	//만약 이번에 들어가야 할 스택위치보다 용량이 작다면 용량을 1칸 늘려준다.
		s->stack = (element*)realloc(s->stack, ++capacity*sizeof(element));
	s->stack[++top] = tmp;			//입력받은 값을 stack에 저장
	printf("S(%d) = ", top+1);
	for(int i = top; i >= 0; i--)
		printf("%d ", s->stack[i]);
	printf("\n\n");
}

void PopStack(StackType *s) {
	int tmp2 = 0;
	
	if(init == 0)	{		//pop명령을 받았을 때 아직 stack이 초기화 되지 않았으면, 초기화 해준다.
		s->stack = (element*)malloc(capacity*sizeof(element));
		init++;
	}

	if(top <= -1) {		//pop명령을 받았을 때 top위치가 stack이 비어있음을 나타낸다면, free로 stack을 반환한다.
		free(s->stack);
		capacity = 1;
		printf("S(%d) = Empty\n\n", top+1);
		init = 0;		//stack이 free되어버렸으니 init은 다시 0이 된다.
		return;
	} else {
		tmp2 = s->stack[top--];
		s->stack = (element*)realloc(s->stack, --capacity*sizeof(element));	//pop하게되면 capacity값을 하나 줄이고 재동적할당함으로써 할당된 크기를 줄인다.
		printf("Popped: %d\n", tmp2);
		if(top <= -1) {
			printf("S(%d) = Empty\n\n", top+1);
		}	else {
			printf("S(%d) = ", top+1);
			for(int i = top; i >= 0; i--)
				printf("%d ", s->stack[i]);
			printf("\n\n");
		}	
	}
}

void PrintMenu()	{
	printf("1. Push\n2. Pop\n3. Quit\n입력) ");
}

int main() {
	StackType s;
	int input = 0, loop = 1;

	while(loop) {
		PrintMenu();
		scanf("%d", &input);
		switch(input) {
			case 1 : PushStack(&s); break;
			case 2 : PopStack(&s); break;
			case 3 : loop = 0; break;
			default: printf("Wrong input..\n");
		}
	}
	return 0;
}
