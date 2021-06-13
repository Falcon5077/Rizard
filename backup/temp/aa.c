#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
typedef char element;
typedef struct { //구조체 타입 선언

element data[MAX_STACK_SIZE];
int top;
} StackType;

void init_stack(StackType *s) //스택 초기화 함수
{
s->top = -1;
}

int is_empty(StackType *s)  //공백 상태 검출 함수
{
return (s->top == -1);
}

int is_full(StackType *s) //포화 상태 검출 함수
{
return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType *s, element item)  //삽입함수
 {
if (is_full(s)){
fprintf(stderr, "스택 포화 에러 \n");
return;
}
else s->data[++(s->top)] = item;
}

element pop(StackType *s) //삭제함수
{
if (is_empty(s)){
  fprintf(stderr, "앙스택 공백 에러\n");
  exit(1);
}
else return s ->data[(s->top)--];
}

element peek(StackType *s)  //피크함수
{
if (is_empty(s)){
 fprintf(stderr, "캌스택 공백 에러\n");
 exit(1);
}
else return s->data[s->top];
}

int prec(char op) //연산자의 우선순위 반환
{
switch(op) {
 case '(': case ')': return 0; //괄호라면 0을 리턴
 case '+': case '-': return 1; //덧셈, 뺼셈이라면 1을 리턴
 case '*': case '/': return 2; //곱셈, 나눗셈이라면 2를 리턴
}
return -1;
}

void eva(char* temp2)
{
	int a;
	int b;
	int result;
	int check = 0;
	for(int p = 0; p < strlen(temp2); p++)
	{
		char ch = temp2[p];
		switch(ch){
			case '+':
				result = temp2[p-1] + temp2[p-2];
				break;
			
		}
		printf("%c ",temp2[p]);
	}

	printf("\n%d \n",result);
}

void infix_to_postfix(char exp[]) //중위표기 수식을 후위표기 수식으로 바꾸기
{
	int i = 0;
	int k = 0;
	char ch, top_op; //문자형태의 변수 선언
	char temp[100];
	int len = strlen(exp); //입력 문자(숫자)열의 갯수 구하기
	StackType s;  //스택타입 s 선언

	init_stack(&s); //스택 초기화
	for(i = 0; i <len; i++){
		 ch = exp[i]; //ch는 입력 문자(숫자)하나하나를 담는다
		 switch(ch){ // 그 담은 것이
			   case '+': case'-': case'*': case'/':
				 while(!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
					temp[k++] = pop(&s);
				 push(&s, ch);  //ch는 push한다
			 break;
			 case '(': //괄호가 (라면
				 push(&s, ch); //push한다
			 break;
	   case ')': //괄호가 )라면
		 top_op = pop(&s); //top_op는 pop한 글자이고
		 while (top_op != '('){ //top_op가 (가 아닌동안
		   temp[k++] = top_op;
		   top_op = pop(&s); //top_op는 pop한 글자이다
		 }
		 break;
		   default: //저런 case가 아니라면
			temp[k++] = ch;
		 break;
	 }
}
	while(!is_empty(&s)) //텅비지 않는 동안
	{
		char asd = pop(&s);
		temp[k++] = asd;
	}
	//	printf("결과 : %s\n",temp);
	eva(&temp[0]);
}
int main(void)
{

	char str[101]; //문자 배열을 101칸 만든다

	scanf("%s", str); //입력 문자열을 str배열에 넣는다
	infix_to_postfix(str); //입력 문자열을 infix_to_postfix로 보낸다
	return 0;
}
