#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int count = atoi(argv[1]);	//atoi를 이용해 char형인 숫자를 int형으로 바꿔 count에 대입한다.
	int arr[10][10] = { 0, };		//2차원배열 선언후 모든 값을 0으로 초기화 한다.
	int j = 1;
		
	for(int i = 0; i < count; i++) {	//for문이 총 4번돌며 count크기에 맞는 사각형을 만든다.
		if(j == 10) j = 1;
		arr[0][i] = j++;
	}
	for(int i = 1; i < count; i++) {	//오른쪽면
		if(j == 10) j = 1;
		arr[i][count-1] = j++;
	}
	for(int i = count-2; i >= 0; i--) {	//아래면
		if(j == 10) j = 1;
		arr[count-1][i] = j++;
	}
	for(int i = count-2; i > 0; i--) {	//왼쪽면
		if(j == 10) j = 1;
		arr[i][0] = j++;
	}

	for(int i = 0; i < count; i++) {		//2중포문이 돌며 배열을 출력한다.
		for(int k = 0; k < count; k++){
			if(arr[i][k] == 0) 							//배열에서 바뀌지않고 초기값 0으로남아았는경우에는 공백으로 표시
				printf("  ");
			else printf("%d ", arr[i][k]);
		}
		printf("\n");
	}
	return 0;
			
}
