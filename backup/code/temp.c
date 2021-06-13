#include <stdio.h>
#include <stdlib.h>

int main(int argc,char * argv[])
{
	int temp;		//사각형의 길이
	if(argc !=2){	//입력된파라메터가 2개 이상이라면 종료
		printf("ERROR : %s [Number] \n",argv[0]);
		return 0;
	}

	temp = atoi(argv[1]);	//입력된 문자열을 int형으로 변환하여 temp에 저장
	int arr[temp][temp];	//temp * temp 크기의 2차원 배열 선언
	int count = 1;			//배열안에 들어갈 count 선언

	for(int i =0; i < temp; i++)	// 2차원 배열을 0으로 초기화 시킴
	{
		for(int j = 0; j <temp; j++)
		{
			arr[i][j] = 0;
		}
	}

	//count가 시계방향으로 저장되어야 하므로
	//왼쪽에서 오른쪽으로
	//위에서 아래로 순차적으로 count를 저장
	for(int i = 0; i < temp; i++)		// 0 ~ temp 까지
	{
		for(int j = 0; j <temp; j++)
		{
			if(arr[i][j] == 0){ // 0이 아니라 다른 수가 저장되어있으면 건너뜀
				if(i==0){		// 맨 윗줄에 count를 저장
					arr[i][j] = count++;
				}
				else if(j == temp-1)	// 맨 오른쪽줄에 count를 저장
				{
					arr[i][j] = count++;
				}
			}

			if(count > 9)	// count가 9가 넘어가면 1로 초기화
				count = 1;
		}
	}
	
	//마찬가지로 count가 시계방향으로 순차적으로 저장되어야 하므로
	//맨 아랫줄은 오른쪽에서 윈쪽으로
	//맨 왼쪽 줄은 아래에서 위로 count를 저장
	for(int i = temp; i > 0; i--)		// 역방향으로 저장해야하므로 i--, j--
	{
		for(int j = temp; j >= 0; j--)
		{
			if(arr[i][j] == 0){	//0이 아니라 다른수가 저장되어있으면 건너뜀
				if(i == temp-1)	// 맨 아랫줄에 count를 오른쪽에서 왼쪽 순으로 저장
					arr[i][j] = count++;
				else if(j == 0)
					arr[i][j] = count++;
			}

			if(count > 9)
				count = 1;
		}
	}

	// 출력
	for(int i =0; i < temp; i++)
	{
		for(int j = 0; j < temp; j++)
		{
			if(arr[i][j] != 0)		// 0이 아니라면 다른수가 저장되어있으므로 출력해줌
				printf("%2d ",arr[i][j]);
			else					// 0이 들어있다면 테두리 부분이 아니라 가운데부분이므로 공백 출력
				printf("   ");
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}
