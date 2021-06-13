#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int eval(char * temp2);
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
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s ->data[(s->top)--];
}

element peek(StackType *s)
{
    if (is_empty(s)){
        fprintf(stderr, "스택 공백 에러\n");
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
    int i = 0;
    int k = 0;
    char ch, top_op;
    char temp[100];
    int len = strlen(exp);
    int z = 0;
    StackType s;
    
    init_stack(&s);
    for(i = 0; i <len; i++){
        ch = exp[i];
        switch(ch){
        case'*': case'/':case '+': case'-':
                while(!is_empty(&s) && (prec(ch) <= prec(peek(&s)))){
                temp[k++] = pop(&s);
            }
            push(&s, ch);
            break;
        case '(':
            push(&s, ch);
        break;
        case ')':
            top_op = pop(&s);
            while (top_op != '('){
                temp[k++] = top_op;
                top_op = pop(&s);
            }
        break;
        default:
            temp[k++] = ch;
        break;
        }
    }
    
    while(!is_empty(&s))
    {
        char asd = pop(&s);
        temp[k++] = asd;
    }
    
    printf("Postfix:%s\n",temp);
    eval(&temp[0]);
}

int eval(char * temp2)
{
    int op1,op2,value;
    int len = strlen(temp2);
    char ch;
    StackType s;
    init_stack(&s);

    for(int i = 0; i < len; i++)
    {
        ch = temp2[i];
        if(ch != '+' && ch != '-' && ch != '*' && ch != '/')
        {
            value = ch-'0';
            push(&s,value);
        }
        else{
            op2 = pop(&s);
            op1 = pop(&s);
            switch(ch)
            {
                case '*': push(&s, op1 * op2); break;
                case '/': push(&s, op1 / op2); break;
                case '+': push(&s, op1 + op2); break;
                case '-': push(&s, op1 - op2); break;
            }
        }
    }
    printf("Result:%d\n",pop(&s));
}

void main(void)
{
    char ans;
    char str[101];
    do{
        printf("Input:");
        scanf("%s", str);
        infix_to_postfix(str);
        
        printf("Again ? <Y/N>");
        getchar();
        scanf("%c",&ans);
        
        if(ans == 'Y')
            continue;
        else if(ans == 'N')
            break;
        else
            break;
    }while(1);

    printf("Bye \n");

    return; 
}
