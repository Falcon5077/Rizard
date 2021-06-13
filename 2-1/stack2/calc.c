#include <stdio.h>
#include <string.h>
#define MAX_NUM 100

typedef char element;
typedef struct {
	element stack[MAX_NUM];
	int top;
}StackType;

void init_stack(StackType *s) {	//스택초기화 함수
	s->top = -1;
}

int is_empty(StackType *s) {	//스택이 비었다면 1출력
	return (s->top == -1);
}

element peek(StackType *s) {
	return s->stack[s->top];
}

element pop(StackType *s) {
	return s->stack[(s->top)--];
}

void push(StackType *s, element item) {
	if(s->top >= MAX_NUM -1) {
		printf("Overflow!\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}

int calculate(char postfix[]) {	//infix_to_postfix함수에서 후위식으로 바꾼 식을 받아 계산
	int op1, op2, value;
	int len = strlen(postfix);	//postfix문자갯수(길이)를 구한다.
	char ch;
	StackType s;

	init_stack(&s);	
	for(int i = 0; i<len; i++){		//postfix의 문자길이만큼 loop
		ch = postfix[i];
		if (ch != '+' && ch != '*' && ch != '-' && ch != '/') {	//ch(i번째postfix값)가 연산자가 아니라면
			value = ch - '0';		//ch값에서 문자0을 빼는것으로 char형에서 int형의 숫자 그자체로 변경
			push(&s, value);
		}
		else {
			op2 = pop(&s);	//op2에 pop값 저장
			op1 = pop(&s);	//op1에 pop값 저장
			switch (ch) {
				case '+': push(&s, op1 + op2); break;
				case '-': push(&s, op1 - op2); break;
				case '/': push(&s, op1 / op2); break;
				case '*': push(&s, op1 * op2); break;
			}
		}
	}
	return pop(&s);	//스택 가장 아래에 남은 결과값을 반환
}

int prec(char op) {		//infix_to_postfix함수에서 사용할 연산자간의 우선순위 출력함수
	switch(op) {
		case '(': case ')': return 0;
		case '+': case '-': return 1;
		case '*': case '/': return 2;
	}
	return -1;
}

void infix_to_postfix(StackType *s, char exp[], char postfix[]){	//입력받은 중위식을 후위식으로 변경하는 함수
	char ch, top_op;
	int len = strlen(exp);
	int j = 0;

	init_stack(s);		//stack top값 초기화
	for(int i = 0; i < len; i++) {	//exp길이만큼 반복
		ch = exp[i];
		switch(ch) {
			case '+': case '-': case '*': case '/':
				while(!is_empty(s) && (prec(ch) <= prec(peek(s)))){	//스택에 값이 있거나, 현재ch의 우선순위가 스택젤 위의 문자보다 낮거나같다면 loop
					printf("%c", peek(s));	//이 경우 젤 위의 값(연산자)를 출력
					postfix[j++] = pop(s);	//출력한 값은 postfix에 순서대로 저장
				}
				push(s, ch);	//i번째 exp(ch)를 스택에 push
				break;
			case '(':	//왼쪽괄호라면
				push(s, ch);	//스택에 삽입
				break;
			case ')':	//오른쪽괄호라면
				top_op = pop(s);	
				while (top_op != '(') {	//'(' 스택에서 왼쪽괄호를 만날때 까지 값들을 출력하고 그 값들은  순서대로 postfix에 저장
					printf("%c", top_op);
					postfix[j++] = top_op;
					top_op = pop(s);
				}
				break;
		default:	//피연산자일경우 바로 출력
				printf("%c", ch);
				postfix[j++] = ch;	//출력되는 값을 바로 postfix에 저장
				break;
		}
	}
	while(!is_empty(s)) {	//for문이 끝나고 stack에 남아있는 피연산자들을 모두 출력
		postfix[j++] = peek(s);	//출력하는 피연산자들은 모두 postfix에 순서대로 저장
		printf("%c", pop(s));
	}
	postfix[j] = '\0';	//후위식으로 변경된 값을 모두 postfix에 저장한 이후, 문자열의 끝을 알리기 위해 \0 입력
}

void PrintMenu(char exp[]) {
	printf("Input: ");
	scanf("%s", exp);
}
void printagain(char again[]){
	printf("Again? <Y/N>");
	scanf("%s", again);
}

int main()
{
	StackType s;
	char again[2];
	char postfix[MAX_NUM];
	char exp[MAX_NUM];
	int loop = 1;
	int result = 0;

	while(loop) {
		PrintMenu(exp);
		printf("Postfix: ");
		infix_to_postfix(&s, exp, postfix);
		result = calculate(postfix);
		printf("\nResult: %d\n\n", result); 
		printagain(again);

		if(again[0] == 'N') {
			loop = 0;
			printf("Bye\n");
		}	
	}
	return 0;	
}
