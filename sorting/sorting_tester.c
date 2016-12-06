
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
#define MAX_NUM 1000000

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
		if (_total > MAX_NUM) {
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
	int auto_restore = 1;

	clock_t time_start, time_end;

	if (!read_data()) {
		return 0;
	}
	memcpy(_numbers, _num_init, sizeof(_num_init[0])*_total);

	do {
		puts("\n==============================================");
		printf("               Sorting (%d integers)\n", _total);
		puts("-----------------Exchange sorts---------------");
		puts("              10. bubble_sort");
		puts("              101. bubble_sort generic");
		puts("              11. cocktail_sort");
		puts("              12. quicksort");
		puts("-----------------Selection sorts--------------");
		puts("              20. selection_sort");
		puts("              21. heapsort");
		puts("-----------------Insertion sorts--------------");
		puts("              30. insertion_sort");
		puts("              31. binary_insertion_sort");
		puts("              32. binary_shellsort");
		puts("              33. shellsort");
		puts("-----------------Merge sorts------------------");
		puts("              40. merge_sort");
		puts("-----------------Distribution sorts-----------");
		puts("              50. counting_sort");
		puts("              51. radix_sort");
		puts("-----------------Hybrid sorts-----------------");
		puts("              60. introsort");
		puts("-------------------COMMAND--------------------");
		puts("              0. restore random state.");
		puts("              1. view all numbers");
		puts("              6. shuffle numbers");
		puts("              7. switch auto-restore");
		puts("              8. re-read data from file");
		puts("              9. exit");
		puts("==============================================");
		printf("          auto-restore is %s\n", auto_restore ? "on" : "off");
		printf("          input index number: ");

input:
		fgets(input_str, sizeof(input_str), stdin);
		input_len = strlen(input_str) - 1;
		for (i = 0; i < input_len; ++i) {
			if (input_str[i] < '0' || input_str[i] > '9') {
				puts("input error, please try again.");
				goto input;
			}
		}
		sscanf(input_str, "%d", &index);

		time_start = clock();
		switch (index) {
		case 10:
			bubble_sort(_numbers, _total);
			break;
		case 101:
			generic_bubble_sort(_numbers, _total, sizeof(_numbers[0]), cmp_int);
			break;
		case 11:
			cocktail_sort(_numbers, _total, sizeof(_numbers[0]), cmp_int);
			break;
		case 12:
			quicksort(_numbers, _total, sizeof(_numbers[0]), cmp_int);
			break;
		case 20:
			selection_sort(_numbers, _total, sizeof(_numbers[0]), cmp_int);
			break;
		case 21:
			puts("\ndoing...\n");
			break;
		case 30:
			insertion_sort(_numbers, _total, sizeof(_numbers[0]), cmp_int);
			break;
		case 31:
			binary_insertion_sort(_numbers, _total, sizeof(_numbers[0]), cmp_int);
			break;
		case 32:
			binary_shellsort(_numbers, _total, sizeof(_numbers[0]), cmp_int);
			break;
		case 33:
			shellsort_2(_numbers, _total, sizeof(_numbers[0]), cmp_int);
			break;
		case 40:
			merge_sort(_numbers, _total, sizeof(_numbers[0]), cmp_int);
			break;
		case 50:
			puts("\ndoing...\n");
			break;
		case 51:
			puts("\ndoing...\n");
			break;
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
		case 6:
			shuffle(_num_init, _total);
			memcpy(_numbers, _num_init, sizeof(_num_init[0])*_total);
			printf("\nall numbers has shuffled.\n");
			break;
		case 7:
			auto_restore = !auto_restore;
			printf("\nauto-restore: %s\n", auto_restore ? "on" : "off");
			break;
		case 8:
			read_data();
			memcpy(_numbers, _num_init, sizeof(_num_init[0])*_total);
			printf("\nthere are %d random numbers.\n", _total);
			break;
		case 9:
			puts("\nsee you :)\n");
			goto over;
		default:
			puts("input error, please try again.");
			goto input;
		}
		time_end = clock();

		if (index > 9) {
			printf("\ncost time: %lf second.\n", difftime(time_end, time_start)/CLOCKS_PER_SEC);
			if (cmp_array(_numbers, _num_init, _total) == 0) {
				if (is_ordered(_numbers, _total)) {
					puts("sort successed. :)");
				} else {
					puts("sort failed! :(");
				}
			} else {
				puts("sort error: value changed, check the algorithm!");
			}
			if (auto_restore) {
				memcpy(_numbers, _num_init, sizeof(_num_init[0])*_total);
				puts("numbers has restored to initial random state.");
			}
		}
		
	} while (1);
	
over:
	return 0;
}
