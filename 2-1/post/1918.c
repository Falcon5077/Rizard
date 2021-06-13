#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100

typedef char element;
typedef struct {
	element stack[MAX_SIZE];
	int top;
} StackType;

void init_stack (StackType *s) {
	s->top = -1;
}

int is_empty(StackType *s) {
	return (s->top <= -1);
}

element peek(StackType *s) {
	return s->stack[s->top];
}

element pop(StackType *s) {
	return s->stack[(s->top)--];
}

void push(StackType *s, char item) {
	s->stack[++(s->top)] = item;
}

int prec(char op) {
	switch(op) {
		case '(': case ')': return 0;
		case '+': case '-': return 1;
		case '*': case '/': return 2;										
	}
	return -1;
}

void infix_to_postfix(char exp[])
{
	int len = strlen(exp);
	char ctmp, top_tmp;
	StackType s;
	init_stack(&s);

	for(int i = 0; i < len; i++)
	{
		ctmp = exp[i];

		switch (ctmp) {
			case '+': case '-': case '/': case'*':
				while(!is_empty(&s) && (prec(ctmp) <= prec(peek(&s))))
					printf("%c", pop(&s));
				push(&s, ctmp);
				break;
			case '(':
				push(&s, ctmp);
				break;
			case ')':
				top_tmp = pop(&s);
				while(top_tmp != '('){
					printf("%c", top_tmp);
					top_tmp = pop(&s);
				}	
				break;
			default:
				printf("%c", ctmp);
				break;
		}
	}
	while (!is_empty(&s))
		printf("%c", pop(&s));
}

int main() {
	char exp[MAX_SIZE];
	scanf("%s", exp);
	infix_to_postfix(exp);
	return 0;
}
