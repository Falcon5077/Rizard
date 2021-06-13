#include <stdio.h>
#include <stdlib.h>

int main(int argc,char * argv[])
{
	int temp;
	
	if(argc != 2){
		printf("EROOR : %s [Number] \n",argv[0]);
		return 0;
	}

	temp = atoi(argv[1]);	// 입력받은 파라메터를 int형 변수인 temp에 저장
	
	for(int i =0; i < temp; i++)	// temp 만큼 for문을 반복해야함 
	{								// Ex) 3이면 3줄짜리 삼각형이 출력되어야함
		for(int j = 0; j < i+1;j++) // 줄바뀜 할때마다 i번째+1 만큼 * 출력
			printf("*");
		printf("\n");
	}

	// i는 temp만큼 줄바꿈
	// j는 *출력을 1회 부터 temp회 까지 반복
	return 0;
}
