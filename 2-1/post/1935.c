#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NUM 100

typedef struct {
	double fnum[MAX_NUM];
	int ftop;
}StackTypeF;

void init_stack(StackTypeF *f){
	f->ftop = -1;
}

void push(StackTypeF *f, double item) {
	f->fnum[++(f->ftop)] = item;
}

double pop(StackTypeF *f) {
	return f->fnum[(f->ftop)--];
}

void extract_alph(char alph[], char exp[]) {
	char call;
	int k = 0;

	for (int i = 0; i < MAX_NUM; i++){
		call = exp[i];
		if(call != '+' && call != '-' && call != '*' && call != '/')
			alph[k++] = call;
	}
}

void change_num(char alph[], double nums[], double c_nums[]) {
	int k = 0;
	char temp = 'k';
	int len = strlen(alph);

	c_nums[0] = nums[0];
	for (int i = 1; i < len; i++){
		if(alph[i] == alph[k])
			c_nums[i] = nums[k];
		else c_nums[i] = nums[++k];
	}
}	

double calculate(char exp[], double nums[])
{
	double op1, op2, value = 0.00;
	int len = strlen(exp);
	int k = 0;
	char ch;
	double c_nums[MAX_NUM];
	char alph[MAX_NUM];
	StackTypeF f;

	init_stack(&f);
	extract_alph(alph, exp);
	change_num(alph, nums, c_nums);
	for(int i = 0; i < len; i++)
	{
		ch = exp[i];
		if(ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			value = c_nums[k];
			push(&f, value);
			k++;
		}
		else {
			op2 = pop(&f);
			op1 = pop(&f);
			switch (ch) {
				case '+': push(&f, op1 + op2); break;
				case '-': push(&f, op1 - op2); break;
				case '*': push(&f, op1 * op2); break;
				case '/': push(&f, op1 / op2); break;
			}
		}
	}	
	return pop(&f);
}

int main()
{
	double result;
	int count;
	double *nums;
	char exp[MAX_NUM];

	scanf("%d", &count);
	nums = (double*)malloc(count * sizeof(double));
	scanf("%s", exp);
	for(int i = 0; i < count; i++)
		scanf("%lf", &nums[i]);
	result = calculate(exp, nums);
	printf("%.2lf\n", result);
	free(nums);
	return 0;
}
