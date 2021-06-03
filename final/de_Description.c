#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DES_MAX_SIZE 1000 //description은 1000byte까지 작성할수있다.

FILE* fp1; //가상의 해석해야 할 bin파일
FILE* fp2; //가상의 결과물 출력 txt파일

//Description
unsigned char des[DES_MAX_SIZE]; //변형된 description저장할 변수
unsigned char txt[DES_MAX_SIZE]; //해석한 description저장할 변수

unsigned char CheckUnchar(unsigned char* tmp){
	unsigned char real;

	if(tmp[0] != tmp[1]){
		if(tmp[0] != tmp[2]){
			if(tmp[1] == tmp[2]){
				real = tmp[1];
			}
			else{
				fprintf(stderr, "ERROR!!\n");
				real = '^';
			}
		}
		else{
			real = tmp[2];
		}
	}
	else{
		real = tmp[0];
	}

	return real;
}


unsigned char ReadUnchar(){
	unsigned char len[3];
	unsigned char m_unchar;

	for(int i=0; i<3; i++){
		fread(&len[i], sizeof(unsigned char), 1, fp1);
	}
	m_unchar = CheckUnchar(len);
	
	return m_unchar;
}

void makedes(){
	int i=0;
	while(!feof(fp1)){
		des[i++] = ReadUnchar();
	}

	des[i-1] = '\0';
}

void ArrToTxt(){
	int i=0; //des배열 반복위한 변수
	int u=0; //txt배열 반복위한 변수

	int n=0; //반복횟수 저장변수
	int d=0; //반복문장 가져올 시 처음부터 검사할 변수

	fp2=fopen("decoded_data1.txt", "w");

	fprintf(fp2, "\n*DESCRIPTION*\n");
	while(des[i]){ //배열 끝까지 반복		
		if(des[i]>= 'A' && des[i]<= 'Z'){ //문자가 반복되지않고 나올때
			txt[u] = des[i++];
			fprintf(fp2, "%c", txt[u++]);
		}
		else if(des[i] == '\n'){ //개행문자가 나올때
			txt[u] = des[i++];
			fprintf(fp2, "%c", txt[u++]);
		}
		else if(des[i]>= '0'-10 && des[i]<= '9'-10){ //한자리 또는 세자리 이상숫자일때
			if(des[i+1]>=3 && des[i+1]<= 28 && des[i+1]!=10){ //세자리 이상 숫자일때
				n=des[i+1];
				for(int k=0; k<n; k++){ //다음칸에 나오는 반복숫자만큼 반복
					txt[u] = des[i]+10;
					fprintf(fp2, "%c", txt[u++]);
				}
				i=i+2;
			}
			else if(des[i+1]==126){ //10번 반복될때
				n=10;
				for(int k=0; k<n; k++){
					txt[u] = des[i]+10;
					fprintf(fp2, "%c", txt[u++]);
				}
				i=i+2;
			}
			else{ //한자리 숫자일때
				txt[u] = des[i++]+10;
				fprintf(fp2, "%c", txt[u++]);
			}
		}
		else if(des[i]>= '0'-20 && des[i]<='9'-20){ //두자리 숫자일때
			txt[u++] = des[i]+20;
			txt[u++] = des[i]+20;
			fprintf(fp2, "%c%c", txt[u-2], txt[u-1]);
			i++;
		}
		else if(des[i]>='a'&& des[i]<='z'){ //반복되는 문자의 경우
			if(des[i+1] >= 3 && des[i+1] <= 28 && des[i+1]!=10){ //세번이상 반복되는 문자
					n=des[i+1];
					for(int k=0; k<n; k++){
						txt[u] = des[i]-32;
						fprintf(fp2, "%c", txt[u++]);
					}
					i=i+2;
			}
			else if(des[i+1]==126){ //10번 반복될때
				n=10;
				for(int k=0; k<n; k++){
					txt[u] = des[i]-32;
					fprintf(fp2, "%c", txt[u++]);
				}
				i=i+2;
			}
			else{ //두번 반복되는 경우
				txt[u++] = des[i]-32;
				txt[u++] = des[i]-32;
				fprintf(fp2, "%c%c", txt[u-2], txt[u-1]);
				i++;
			}
		}
		else if(des[i] == '='){ //문장반복구문 나올경우
			n=des[i+1];

			while(n!=1){
				if(txt[d] == '\n'){
					n=n-1;
				}
				d++;
			}

			while(txt[d]!='\n'){
				txt[u] = txt[d++];
				fprintf(fp2, "%c", txt[u++]);
			}

			i=i+2;
		}
		else{ //에러
			fprintf(stderr, "\nERROR!!!!!\n");
			fprintf(fp2, "%c", des[i]);
			i++;
		}

	}
	fclose(fp2);
}

int main(){
	fp1=fopen("encoded_data1.bin", "rb");
	if(fp1==NULL){
		fprintf(stderr, "ERROR_OPEN!!\n");
	}

	makedes();
	ArrToTxt();

	fclose(fp1);
	return 0;
}
