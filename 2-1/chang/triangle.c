#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int count;
	count = atoi(argv[1]); 
	//atoi함수를 이용해 argv에 char형으로 저장된 숫자를 int형으로 바꾸어 count에 넣는다.

	for(int i = 1; i <= count; i++) {	//2중for문을 돌며 count횟수만큼 별을 찍는다.
		for(int j= 0; j < i; j++) {
			printf("*");
		}
		printf("\n");
	}
	return 0;
}
	
