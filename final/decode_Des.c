#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DES_MAX_SIZE 1000 //description은 1000byte까지 작성할수있다.

FILE* fp; //가상의 해석해야 할 bin파일
FILE* decode; //가상의 결과물 출력 txt파일

char des[DES_MAX_SIZE]; //변형된 description저장할 변수
char txt[DES_MAX_SIZE]; //해석한 description저장할 변수

//바이너리파일에서 배열로 저장해오는 함수
void BinToArr(){
	char check[3]= { 0 }; //3문자씩 받아와 확인할 임시변수
	int i=0; //배열 반복위한 변수
	
	fp=fopen("encoded_data1.bin", "rb");

	do{
		fread(&check, sizeof(char)*3, 1, fp); //임시변수에 char크기만큼 3개를 불러옴

		if(check[0] == check[1]){ //첫번째와 두번째가 같을때
			des[i] = check[0];
		}
		else if(check[1] == check[2]){ //두번째와 세번째가 같을때
			des[i] = check[1];
		}
		else if(check[2] == check[0]){ //첫번째와 세번째가 같을
			des[i] = check[2];
		}
		else
			des[i] == '?'; //받아온 3바이트가 다 다를경우 == ERROR
		
		i++;

		
	}while(!feof(fp));

	des[i-1] = '\0';

	fclose(fp);
	
}

void ArrToTxt(){
	int i=0; //des배열 반복위한 변수
	int u=0; //txt배열 반복위한 변수
	int n=0; //반복횟수 저장변수
	int d=0;
	char tmp[20]; //동일문장 복사위한 변수

	int a=0, b=15; //반복횟수 구분위한 변수
	char zero = a;
	char max = b;
	
	decode=fopen("decoded_data1.txt", "w");

	fprintf(decode, "\n*DESCRIPTION*\n");
	
	while(des[i] != '\0'){ //배열 끝까지 반복		
		if(des[i]>= 'A' && des[i]<= 'Z'){ //문자가 반복되지않고 나올때
			txt[u] = des[i];
			fprintf(decode, "%c", txt[u]);
			u++;
			i++;
		}
		else if(des[i] == '\n'){ //개행문자가 나올때
			txt[u] = des[i];
			fprintf(decode, "%c", txt[u]);
			u++;
			i++;
		}
		else if(des[i]>= '0'-10 && des[i]<= '9'-10){ //한자리 또는 세자리 이상숫자일때
			if(des[i+1]>=zero && des[i+1]<= max){ //세자리 이상 숫자일때
				n=des[i+1];
				for(int k=0; k<n; k++){ //다음칸에 나오는 반복숫자만큼 반복
					txt[u] = des[i]+10;
					fprintf(decode, "%c", txt[u]);
					u++;
				}
				i=i+2;
			}
			else{ //한자리 숫자일때
				txt[u] = des[i]+10;
				fprintf(decode, "%c", txt[u]);
				u++;
				i++;
			}
		}
		else if(des[i]>= '0'-20 && des[i]<='9'-20){ //두자리 숫자일때
			txt[u] = des[i]+20;
			txt[u+1] = des[i]+20;
			fprintf(decode, "%c%c", txt[u], txt[u+1]);
			i++;
			u=u+2;
		}
		/*else if(des[i]>=zero  && des[i]<=max){ //반복되는 문자의 경우
			if(des[i+1] >= '0' && des[i+1] <= '9'){ //세번이상 반복되는 문자
					n=des[i+1];
					for(int k=0; k<n; k++){
						txt[u] = des[i]-32;
						fprintf(decode, "%c", txt[u]);
						u++;
					}
					i=i+2;
			}
			else{ //두번 반복되는 경우
				txt[u++] = des[i]-32;
				txt[u++] = des[i]-32;
				fprintf(decode, "%c%c", txt[u-2], txt[u-1]);
				i++;
			}
		}
		else if(des[i] == '='){ //문장반복구문 나올경우
			n=des[i+1];
			
			for(int k=0; k<n; k++){ //tmp에 반복문장 집어넣기
				while(txt[d]=='\n');{
					tmp[d] = txt[d];
					d++;
				}
				if(k!=n-1)
					tmp[0] = '\0';
			}

			d=0;
			while(tmp[d] == '\0'){ //tmp끝까지 0번째부터 txt에 저장
				txt[u] = tmp[d];
				fprintf(decode, "%c", txt[u]);
				u++;
				d++;
			}
		}*/
		else{ //에러
			fprintf(decode, "\nERROR!!!!!\n");
			exit(1);
		}
	}

	fclose(decode);
}

int main(){
	BinToArr();
	ArrToTxt();
	return 0;
}
