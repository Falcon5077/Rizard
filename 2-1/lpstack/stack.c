#include <stdio.h>
#define MAX_STACK_SIZE 50

int S_top = -1;
typedef struct {
	int stack[MAX_STACK_SIZE];
}	StackType;

void PushStack(StackType *s) {
	int tmp = 0;

	if(S_top >= (MAX_STACK_SIZE - 1)) {
		printf("Stack Overflow!\n");
		return;
		}else {
			printf("Push: ");
			scanf("%d", &tmp);
			s->stack[++S_top] = tmp;
			printf("S(%d) = ", S_top + 1);
			for(int i = S_top; i >= 0; i--)
				printf("%d ", s->stack[i]);
			printf("\n\n");
		}
}

void PopStack(StackType *s) {
	int tmp2 = 0;
	
	if(S_top == -1) {
		printf("S(%d) = Empty\n\n",S_top +1);
		return;
	}	else {
			tmp2 = s->stack[S_top--];
			printf("Popped: %d\n", tmp2);
			if(S_top == -1) {
				printf("S(%d) = Empty\n\n", S_top+1);
			}else {
			printf("S(%d) = ", S_top + 1);
			for(int i = S_top; i >= 0; i--)
				printf("%d ",s->stack[i]);
			printf("\n\n");
			}
	}	
}

void PrintMenu() {
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
