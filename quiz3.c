/*5532605 김형래
	2021.05.02
	추가점수 코드
	메인함수에선 정수가 9 다음으로 넘어갈때 10, 11을 그대로 출력한다 가정 하에	계산을 하며, cal_ans에서 9에서 1로 넘어가게 변환해 준다.*/

#include <stdio.h>
#include <stdlib.h>

int cal_ans(int ans); //출력값을 계산해주는 함수

int main(int argv, char *argc[])
//매개변수로 정수와 문자열을 받음. argc에문자열 갯수, argv에 문자열 받음
{
	if(argc[1]==NULL){
		printf("usage) quiz2.out number\n"); //실행시 받은 문자열이 없으면 출력
		return 0; //프로그램 종료
	}

	int num= atoi(argc[1]);
 	//argv[1]에 받은 문자를 int형으로 변환 후 num에 저장

	for(int i=1; i<=num; i++) //줄넘겨주는 반복구문
	{
		for(int j=1; j<=num; j++) 
		//각줄 안에서 가로로 한칸씩 num까지 넘겨주는반복구문
		{
			if(i==1){ //첫번째 줄(행)일때 출력
				printf("%d ", cal_ans(j)); //j값을 그대로 전달하며cal_ans 함수호출
			}
			else if(i==num){ //마지막 줄(행)일때 출력
				printf("%d ",cal_ans(3*num-2-(j-1)));
				//마지막 행에서의 각 칸의 값을 계산해주는 식을 전달하며 함수 호출
			}
			else{
				if(j==1) //가운데 줄(행)일때 첫번째 칸 출력
					printf("%d ", cal_ans(4*(num-1)-(i-2)));
					//가운데 행에서 첫번째칸의 값을 계산해주는 식을 전달하며 함수 호출
				else if(j==num) //가운데 줄(행)일때 마지막 칸 출력
					printf("%d ", cal_ans(num+(i-1)));
					//가운데 행에서 마지막칸의 값을 계산해주는 식을 전달하며 함수 호출
				else //가운데 줄(행)에서 가운데 칸들을 빈칸으로 출력
					printf("  ");
			}
		}
	
		printf("\n"); //줄(행) 넘김
	}

	return 0;
}

int cal_ans(int ans) // 각 칸에 출력할 값을 변환해주는 함수
{
	if(ans<10) //출력할 값이 한자리 수일때
		return ans;//그대로 출력
	else{ //출력할 값이 두자리 수일때
		ans+=1; //값에 1을 더한다
		return cal_ans(ans-10);
	 	//10을 빼고 뺀 값을 인자로 전달하면서 함수를 다시 호출한다
	}
}
