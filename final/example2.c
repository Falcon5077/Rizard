#include <stdio.h>
#include <string.h>

int main(){
	int zero = 0;
	int max = 15;
	char a = zero;
	char b = max;
	int k=0;
	
	int mac = 8;
	char mac_c = mac;

	if(mac>=zero && mac<=max){
		k = mac;
		printf("%d, true\n", k);
	}

	return 0;


}
