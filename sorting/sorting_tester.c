
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "distribution_sorts.h"
#include "exchange_sorts.h"
#include "hybrid_sorts.h"
#include "insertion_sorts.h"
#include "merge_sorts.h"
#include "selection_sorts.h"

#define MAX_INPUT 64
#define MAX_NUM 2200000

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

int tmpA[MAX_NUM];
int tmpB[MAX_NUM];
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
int num_input[MAX_NUM] = {0};
// the data to sort
int num_buf[MAX_NUM] = {0};

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
		if (total >= MAX_NUM) {
			puts("file content error, too more data!");
			fclose(fin);
			return 0;
		}
	}
	fclose(fin);
	return 1;
}

int main(void/*int argc, char *argv[]*/)
{
	int i, index;
	int input_len = 0;
	char input_str[MAX_INPUT] = {0};
	char is_quit = 0;

	clock_t time_start, time_end;

	if (!read_data()) {
		return 0;
	}
	memcpy(num_buf, num_input, sizeof(num_input[0])*total);

	do {
		puts("==============================================");
		printf("               Sorting (%d integers)\n", total);
		puts("-----------------Exchange sorts---------------");
		puts("               10. bubble_sort");
		puts("               11. cocktail_sort");
		puts("               12. quick_sort");
		puts("-----------------Selection sorts--------------");
		puts("               20. select_sort");
		puts("               21. heap_sort");
		puts("-----------------Insertion sorts--------------");
		puts("               30. insert_sort");
		puts("               31. binary_insert_sort");
		puts("               32. shell_sort_1");
		puts("               33. shell_sort_2");
		puts("               34. binary_shell_sort");
		puts("-----------------Merge sorts------------------");
		puts("               40. merge_sort");
		puts("-----------------Distribution sorts-----------");
		puts("               50. counting_sort");
		puts("               51. radix_sort");
		puts("-----------------Hybrid sorts-----------------");
		puts("               60. intro_sort");
		puts("-------------------COMMAND--------------------");
		puts("               00. restore random state.");
		puts("               01. view all numbers");
		puts("               08. re-read data from file");
		puts("               09. exit");
		puts("==============================================");
		printf("input index number: ", total);

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
			// --- Exchange sorts
		case 10:
			bubble_sort(num_buf, total, sizeof(num_buf[0]), cmp_int);
			break;
		case 11:
			puts("\ndoing...\n");
			//cocktail_sort(num_buf, total, sizeof(num_buf[0]), cmp_int);
			break;
		case 13:
			puts("\ndoing...\n");
			break;
			// --- Selection sorts
		case 20:
			select_sort(num_buf, total, sizeof(num_buf[0]), cmp_int);
			break;
		case 21:
			puts("\ndoing...\n");
			break;
			// --- Insertion sorts
		case 30:
			insert_sort(num_buf, total, sizeof(num_buf[0]), cmp_int);
			break;
		case 31:
			binary_insert_sort(num_buf, total, sizeof(num_buf[0]), cmp_int);
			break;
		case 32:
			shell_sort_1(num_buf, total, sizeof(num_buf[0]), cmp_int);
			break;
		case 33:
			shell_sort_2(num_buf, total, sizeof(num_buf[0]), cmp_int);
			break;
		case 34:
			binary_shell_sort(num_buf, total, sizeof(num_buf[0]), cmp_int);
			break;
			// --- Merge sorts
		case 40:
			puts("\ndoing...\n");
			break;
			// --- Distribution sorts
		case 50:
			puts("\ndoing...\n");
			break;
		case 51:
			puts("\ndoing...\n");
			break;
			// Hybrid sorts
		case 60:
			puts("\ndoing...\n");
			break;
		case 0:
			memcpy(num_buf, num_input, sizeof(num_input[0])*total);
			printf("\nthere are %d random numbers.\n", total);
			break;
		case 1:
			print_array(num_buf, total);
			break;
		case 8:
			read_data();
			printf("\nthere are %d random numbers.\n", total);
			break;
		case 9:
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
		if (index > 9 && index <= 90) {
			if (is_array_equal(num_buf, num_input, total)) {
				if (is_ordered(num_buf, total))
					printf("\nsort successed. :)");
				else
					printf("\nsort failed! :(");
			} else {
				printf("\nsort error: value changed. \n"
					"\tdo other sorting, please restore random state first. \n"
					"\tcheck your algorithm.");
				//memcpy(num_buf, num_input, sizeof(num_input[0])*total);
			}
			printf("\ncost time: %lf second \n", difftime(time_end, time_start)/CLK_TCK);
		}
		//system("pause");
		//system("cls");
	} while (!is_quit);
	return 0;
}
