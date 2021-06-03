#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//User_Status
unsigned char *id;
unsigned char idLen;
unsigned char *name;
unsigned char nameLen;
unsigned char gender;
unsigned char age;
unsigned char HP;
unsigned char MP;
unsigned short coin;

//Items
char* Items[] = {
    "BOMB",
    "POSTION",
    "CURE",
    "BOOK",
    "SHIELD",
    "CANNON"
};

int main(int argc, char *argv[]) {
	char *fNAME;
	
	if (argc != 2) {
		printf("Error...\n");
		return 0;
	}

  fNAME = argv[1];

  FILE *fp = fopen(fNAME, "r");

  if(fp == NULL) {
		fprintf(stderr, "Error...\n");
    exit(1);
	}

  char buffer[1000];
	char *user[7];			//user 정보 저장 포인터 배열
	char *friend[4];
	char *item_save[5];
	char *des[1000];
  char *test;					
  char *tmp;
	char *ch;
	char des_buff[1000], friend_buff[1000], item_save_buff[1000], user_buff[1000];

	int count_user = 0;			//user 정보 받기 위한 count 변수
	int count_item = 0;			//Item 정보 받기 위한 count 변수
	int count_friend = 0;		//동맹 정보 받기 위한 count 변수
	int line = 0;
	int index = 0;
	int x = 0, z= 0, c = 0, v = 0;
	int plz = 0;

  while(!feof(fp)) {
		test = fgets(buffer, 1000, fp);

		if(test == NULL) {
			break;
		}

		if(strstr(test, "*")) {								//필드 검사 if문
			printf("%d 번째 필드\n", ++index);
      continue;
		}
		
    switch(index) {
			case 1 : tmp = strstr(test, ":");				//tmp에 :값부터 저장							 
							 if(tmp != NULL) {							
								 if(index != 1) {
									 exit(1);
								 }
								 user[count_user] = &tmp[2];
								 for(int k = 0; k < strlen(user[count_user]); k++)
									 user_buff[v++] = user[count_user][k];
							 }
							 break;

 			case 2 : tmp = strstr(test, ":");
							 if(tmp != NULL) {
								 if(index != 2) {
									 exit(1);
								 }
								 item_save[count_item] = &tmp[2];
								 for(int k = 0; k < strlen(item_save[count_item]); k++)
									 item_save_buff[c++] = item_save[count_item][k];
							 }
							 break;

 		  case 3 : tmp = strstr(test, ":");
							 if(tmp != NULL) {
								 if(index != 3) {
									 exit(1);
								 }
								 friend[count_friend] = &tmp[2];
								 for(int k = 0; k < strlen(friend[count_friend]); k++) 
									 friend_buff[z++] = friend[count_friend][k];

								 plz++;
							 }
							 break;

			case 4 : tmp = strstr(test, "\0");
							 if(tmp != NULL) {
								 if(index != 4) {
									 exit(1);
								 }
								 des[line] = &tmp[0];
								 for(int k = 0; k < strlen(des[line]); k++)
									 des_buff[x++] = des[line][k];
								 break;
							 }
		}
	}
	
	user_buff[v++] = '\0';
	item_save_buff[c++] = '\0';
	friend_buff[z++] = '\0';
	des_buff[x++] = '\0';

	plz = plz / 4;

	printf("user: \n%s", user_buff);
	printf("item: \n%s", item_save_buff);
	printf("friend: \n%s", friend_buff);
	printf("description: \n%s", des_buff);	
	printf("count: %d\n", plz);

	fclose(fp);

	return 0;
}
