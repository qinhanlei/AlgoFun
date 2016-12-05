
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
#define MAX_NUM 900000

int _total = 0;
int _num_init[MAX_NUM] = {0};
int _numbers[MAX_NUM] = {0};

int _tmpA[MAX_NUM];
int _tmpB[MAX_NUM];


void print_array(int arr[], size_t n) {
	size_t i;
	for (i = 0; i < n; ++i) {
		//if (i % 5 == 0) puts("");
		printf("%d \n", arr[i]);
	}
	printf("\n");
}


int cmp_int(const void* a, const void* b) {
	int p = *(int*)a;
	int q = *(int*)b;
	if (p < q) return -1;
	if (p > q) return 1;
	return 0;
}


int cmp_array(const int arrA[], const int arrB[], size_t n) {
	memcpy(_tmpA, arrA, sizeof(arrA[0]) * n);
	memcpy(_tmpB, arrB, sizeof(arrB[0]) * n);
	qsort(_tmpA, n, sizeof(_tmpA[0]), cmp_int);
	qsort(_tmpB, n, sizeof(_tmpB[0]), cmp_int);
	return memcmp(_tmpA, _tmpB, sizeof(_tmpA[0]) * n);
}


int is_ordered(int arr[], size_t n) {
	size_t i;
	for (i = 0; i < n - 1; ++i)
		if (arr[i] > arr[i + 1])
			return 0;
	return 1;
}


int read_data() {
	int tmp;
	static char filename[] = "./random_num.txt";
	FILE* fp = fopen(filename, "r");
	if (!fp) {
		printf("open file '%s' error!\n", filename);
		return 0;
	}

	_total = 0;
	while (fscanf(fp, "%d", &tmp) != EOF) {
		_num_init[_total++] = tmp;
		if (_total >= MAX_NUM) {
			puts("file content error, too more data!");
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);
	return 1;
}


int main(int argc, char *argv[]) {
	int i, index;
	int input_len = 0;
	char input_str[MAX_INPUT] = {0};
	char is_quit = 0;

	clock_t time_start, time_end;

	if (!read_data()) {
		return 0;
	}
	memcpy(_numbers, _num_init, sizeof(_num_init[0])*_total);

	do {
		puts("\n==============================================");
		printf("               Sorting (%d integers)\n", _total);
		puts("-----------------Exchange sorts---------------");
		if (_total <= 5000) {
			puts("               10. bubble_sort"); // 9w
			puts("               11. cocktail_sort");
		}
		puts("               12. quick_sort");
		puts("-----------------Selection sorts--------------");
		if (_total <= 20000) {
			puts("               20. select_sort");
		}
		puts("               21. heap_sort");
		puts("-----------------Insertion sorts--------------");
		if (_total <= 20000) {
			puts("               30. insert_sort");			
		}
		if (_total <= 200000) {
			puts("               31. binary_insert_sort");			
		}
		puts("               32. binary_shell_sort");
		puts("               33. shell_sort");
		puts("-----------------Merge sorts------------------");
		puts("               40. merge_sort");
		puts("-----------------Distribution sorts-----------");
		puts("               50. counting_sort");
		puts("               51. radix_sort");
		puts("-----------------Hybrid sorts-----------------");
		puts("               60. intro_sort");
		puts("-------------------COMMAND--------------------");
		puts("                0. restore random state.");
		puts("                1. view all numbers");
		puts("                8. re-read data from file");
		puts("                9. exit");
		puts("==============================================");
		printf("          input index number: ");

		fgets(input_str, sizeof(input_str), stdin);
		input_len = strlen(input_str) - 1;
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
			bubble_sort(_numbers, _total, sizeof(_numbers[0]), cmp_int);
			break;
		case 11:
			cocktail_sort(_numbers, _total, sizeof(_numbers[0]), cmp_int);
			break;
		case 12:
			quick_sort(_numbers, _total, sizeof(_numbers[0]), cmp_int);
			break;
			// --- Selection sorts
		case 20:
			select_sort(_numbers, _total, sizeof(_numbers[0]), cmp_int);
			break;
		case 21:
			puts("\ndoing...\n");
			break;
			// --- Insertion sorts
		case 30:
			insert_sort(_numbers, _total, sizeof(_numbers[0]), cmp_int);
			break;
		case 31:
			binary_insert_sort(_numbers, _total, sizeof(_numbers[0]), cmp_int);
			break;
		case 32:
			binary_shell_sort(_numbers, _total, sizeof(_numbers[0]), cmp_int);
			break;
		case 33:
			shell_sort_2(_numbers, _total, sizeof(_numbers[0]), cmp_int);
			break;
			// --- Merge sorts
		case 40:
			merge_sort(_numbers, _total, sizeof(_numbers[0]), cmp_int);
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
			memcpy(_numbers, _num_init, sizeof(_num_init[0])*_total);
			printf("\nthere are %d random numbers.\n", _total);
			break;
		case 1:
			print_array(_numbers, _total);
			break;
		case 8:
			read_data();
			memcpy(_numbers, _num_init, sizeof(_num_init[0])*_total);
			printf("\nthere are %d random numbers.\n", _total);
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

		if (index > 9 && index <= 90) {
			printf("\ncost time: %lf second.\n", difftime(time_end, time_start)/CLOCKS_PER_SEC);
			if (cmp_array(_numbers, _num_init, _total) == 0) {
				if (is_ordered(_numbers, _total)) {
					puts("sort successed. :)");
				} else {
					puts("sort failed! :(");
				}
			} else {
				puts("sort error: value changed. \n"
					"\tdo other sorting, please restore random state first. \n"
					"\tcheck your algorithm.");
				//memcpy(_numbers, _num_init, sizeof(_num_init[0])*_total);
			}
		}
		
	} while (!is_quit);
	
	return 0;
}
