
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"


int main(int argc, char* argv[]) {
	int i;
	int num = 0;
	char filename[] = "./random_num.txt";
	int* numbers = NULL;
	FILE* fp = NULL;
	
	srand((unsigned)time(NULL));
	printf("RAND_MAX:%d\n", RAND_MAX);
	printf("How many random numbers you want in '%s': ", filename);
	
	scanf("%d", &num);
	fp = fopen(filename, "w");
	if (!fp) {
		printf("create file '%s' failed!", filename);
		return 0;
	}
	fprintf(fp, "%d\n", num);
	
	numbers = malloc(num * sizeof(int));
	for (i = 0; i < num; ++i) {
		numbers[i] = i;
	}
	shuffle(numbers, num);
	
	for (i = 0; i < num; ++i) {
		fprintf(fp, "%d\n", numbers[i]);
	}
	fflush(fp);
	fclose(fp);
	
	return 0;
}
