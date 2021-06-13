#include <stdio.h>
#include <stdlib.h>

int main(int argc,char * argv[])
{
	int temp;
	if(argc !=2){
		printf("ERROR : %s [Number] \n",argv[0]);
		return 0;
	}

	temp = atoi(argv[1]);
	int arr[temp][temp];
	int count = 0;

	for(int i =0; i < temp; i++)
	{
		for(int j = 0; j <temp; j++)
		{
			arr[i][j] = 0;
		}
	}

	for(int i = 0; i < temp; i++)
	{
		for(int j = 0; j <temp; j++)
		{
//			if(i == 0 || i == temp-1 || j == temp-1 || j ==0 ){
			if(i==0 && arr[i][j] == 0){
				arr[i][j] = count++;
				printf("%2d ",arr[i][j]);
			}
			else if(j == temp-1 && arr[i][j] == 0)
			{
				arr[i][j] = count++;
				printf("%2d ",arr[i][j]);
			}
			else if(i == temp-1 && arr[i][j] == 0)
			{
				arr[i][j] = count++;
				printf("%2d ",arr[i][j]);
			}
			else if(j == 0 && arr[i][j] == 0)
			{
				arr[i][j] = count++;
				printf("%2d ",arr[i][j]);
			}
			else
				printf("   ");
		}
		printf("\n");
	}
	for(int i = temp; i > 0; i++)
	{
		for(int j = temp; j > 0; j--)
		{
			if(i == temp-1 && arr[i][j] == 0)
				arr[i][j] = count++;
		}
	}
	
	printf("\n");

	return 0;
}
