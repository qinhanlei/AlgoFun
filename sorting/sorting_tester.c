
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "bubble_sort.h"
#include "select_sort.h"
#include "insert_sort.h"

#define MAX_INPUT 64
#define MaxN 1000000

void print_array(int arr[], size_t n)
{
	size_t i;
	for (i = 0; i < n; ++i) {
		//if (i % 5 == 0) puts("");
		printf("%d \n", arr[i]);
	}
	printf("\n");
}

int cmp_int(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

int tmpA[MaxN];
int tmpB[MaxN];
// is array content equal
int is_array_equal(const int arrA[], const int arrB[], size_t n)
{
	memcpy(tmpA, arrA, sizeof(arrA[0]) * n);
	memcpy(tmpB, arrB, sizeof(arrB[0]) * n);
	qsort(tmpA, n, sizeof(tmpA[0]), cmp_int);
	qsort(tmpB, n, sizeof(tmpB[0]), cmp_int);
	if (memcmp(tmpA, tmpB, sizeof(tmpA[0]) * n) == 0)
		return 1;
	else 
		return 0;
}

int is_ordered(int arr[], size_t n)
{
	size_t i;
	for (i = 0; i < n - 1; ++i)
		if (arr[i] > arr[i + 1])
			return 0;
	return 1;
}

int total = 0;
// the data of original
int num_input[MaxN] = {0};
// the data to sort
int num_buf[MaxN] = {0};

int read_data()
{
	int tmp;
	FILE *fin = fopen("random_num.txt", "r");
	if (!fin) {
		puts("open file \"random_num.txt\" error!");
		return 0;
	}

	total = 0;
	while (fscanf(fin, "%d", &tmp) != EOF) {
		num_input[total++] = tmp;
		if (total >= MaxN) {
			puts("file content error, too more data!");
			return 0;
		}
	}
	printf("got %d random numbers from file.\n", total);
	return 1;
}

int main(int argc, char *argv[])
{
	int i, index;

	char is_quit = 0;
	char input_str[MAX_INPUT] = {0};
	int input_len = 0;

	clock_t time_start, time_end;

	if (!read_data()) {
		return 0;
	}
	memcpy(num_buf, num_input, sizeof(num_input[0])*total);

	while (1) {
		puts("");
		puts("======================================");
		puts("               Sorting ");
		puts("--------------------------------------");
		puts("\t00. restore random state.");
		puts("----------------O(n^2)----------------");
		puts("\t01. bubble_sort");
		puts("\t02. cocktail_sort (variant from bubble sort)");
		puts("\t03. select_sort");
		puts("\t04. insert_sort");
		puts("\t05. binary_insert_sort");
		puts("---------------O(nlogn)---------------");
		puts("\t06. shell_sort");
		puts("\t07. heap_sort");
		puts("\t08. merge_sort");
		puts("\t09. quick_sort");
		puts("--------------------------------------");
		puts("\t98. view all numbers");
		puts("\t99. exit");
		puts("======================================");
		printf("\tinput number: ");

		fgets(input_str, sizeof(input_str), stdin);
		input_len = strlen(input_str) - 1;
		// check the input
		for (i = 0; i < input_len; ++i) {
			if (input_str[i] < '0' || input_str[i] > '9') {
				puts("input error, please try again.");
				break;
			}
		}
		if (i != input_len) {
			continue;
		}
		sscanf(input_str, "%d", &index);

		time_start = clock();
		switch (index) {
		case 0:
			memcpy(num_buf, num_input, sizeof(num_input[0])*total);
			printf("\nthere are %d random numbers.\n", total);
			break;
		case 1:
			bubble_sort(num_buf, total, sizeof(num_buf[0]), cmp_int);
			break;
		case 2:
			cocktail_sort(num_buf, total, sizeof(num_buf[0]), cmp_int);
			break;
		case 3:
			select_sort(num_buf, total, sizeof(num_buf[0]), cmp_int);
			break;
		case 4:
			insert_sort(num_buf, total, sizeof(num_buf[0]), cmp_int);
			break;
		case 5:
			puts("\ndoing...\n");
			break;
		case 6:
			puts("\ndoing...\n");
			break;
		case 7:
			puts("\ndoing...\n");
			break;
		case 8:
			puts("\ndoing...\n");
			break;
		case 9:
			puts("\ndoing...\n");
			break;
		case 98:
			print_array(num_buf, total);
			break;
		case 99:
			is_quit = 1;
			break;
		default:
			puts("\nwrong input!");
			continue;
		}
		time_end = clock();

		if (is_quit) {
			puts("\nsee you :)\n");
			break;
		}

		// is that sort operate
		if (index > 0 && index <= 9) {
			if (is_array_equal(num_buf, num_input, total)) {
				if (is_ordered(num_buf, total))
					printf("\nsort successed. ");
				else
					printf("\nsort failed. ");
			} else {
				printf("\nsort error: value changed. \n"
					"\tdo other sorting, please restore random state first. \n"
					"\tcheck your algorithm.");
				//memcpy(num_buf, num_input, sizeof(num_input[0])*total);
			}
			printf("\ncost time: %lf second \n", difftime(time_end, time_start)/CLK_TCK);
		}
	}
	system("pause");
	return 0;
}
