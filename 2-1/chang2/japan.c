#include <stdio.h>
#include <string.h>
#define MAX_SIZE 255

int input() {
	char name[MAX_SIZE][MAX_SIZE];
	int k, size, count = 0;
	int clnum;
	double dbl;
	char order;
	FILE *fp = fopen("japan.bin", "wb");
	
	printf("class number: ");
	scanf(" %d", &clnum);

	printf("coordinate: ");
	scanf(" %lf", &dbl);

	for(int i = 0; k != 1; i++) {
		printf("input_name: ");
		scanf(" %s", name[i]);
		count++;
		printf("name[%d]: %s\n", i, name[i]);
		printf("Again?: ");
		scanf(" %c", &order);
		if(order == 'N') k = 1;
	}
	
	fwrite(&clnum, sizeof(int), 1, fp);
	fwrite(&dbl, sizeof(double), 1, fp);

	fwrite(&count, sizeof(int), 1, fp);
	for(int i = 0; i < count; i++)
		fwrite(name[i], strlen(name[i]), 1, fp);

	fclose(fp);
}

int output() {
	int size, count, clnum;
	double dbl;
	char name[MAX_SIZE][MAX_SIZE];
	FILE *fp = fopen("japan.bin", "rb");
	
	fread(&clnum, sizeof(int), 1, fp);
	fread(&dbl, sizeof(double), 1, fp);

	fread(&count, sizeof(int), 1, fp);
	for(int i = 0; i < count; i++)
		fread(name[i], 5, 1, fp);

	printf("class number: %d\n", clnum);
	printf("coordinate: %.3f\n", dbl);
	for(int i = 0; i < count; i++)
		printf("%s\n", name[i]);

	fclose(fp);
}

int main() {
	int order;
	int loop = 1;
	
	while(loop) {
		printf("1. input\n2.output\ninsert> ");
		scanf("%d", &order);
		switch(order) {
			case 1: input(); break;
			case 2: output(); break;
			case 3: loop =  0; break;
		}
	}


	return 0;
}
