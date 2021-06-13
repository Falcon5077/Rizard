#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef char element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

void init_stack(StackType *s)
{
	s->top = -1;
}


int is_empty(StackType *s)
{
	return (s->top == -1);
}

int is_full(StackType *s)
{

	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType *s, element item)
{
	if (is_full(s)){
		fprintf(stderr, "스택 포화 에러 \n");
		return;
	}
	else s->data[++(s->top)] = item;
}

element pop(StackType *s)
{
	if (is_empty(s)){
		fprintf(stderr, "스택 공백 에러1 \n");
	exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(StackType *s)
{
	if (is_empty(s)){
		fprintf(stderr, "스택 공백 에러2 \n");
		exit(1);
	}
	else return s->data[s->top];
}

 int prec(char op)
 {
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
	char ch;
	char top_op;
	StackType s;

	init_stack(&s);

	for(int i = 0; i < len; i++)
	{
		ch = exp[i];
		//top_op = ch;
		switch(ch){
			case '+':
			case '-':
			case '*':
			case '/':			
			while(!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
				printf("%c",top_op);
			push(&s,ch);
			break;

			case '(':
				push(&s,ch);
				break;
			case ')':
				top_op = pop(&s);
				while(top_op != '('){
					printf("%c",top_op);					
					top_op = pop(&s);
				}
				break;
			default:
				printf("%c",ch);
				break;
				
		}
	}
	while(!is_empty(&s))
		printf("%c",pop(&s));

	printf("\n");

//	printf("\nlength : %d \n",len);
	
	return;
}

int main(void)
 {
   char str[101];
   scanf("%s", str);
   infix_to_postfix(str);
   return 0;
 }

