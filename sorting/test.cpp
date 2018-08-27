
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <iostream>
#include <algorithm>

#include "common.h"
#include "sorts.h"


int _auto_restore = 1;

int _total = 1000000;
int* _initnum = NULL;
int* _numbers = NULL;


bool same_collection(const int arr1[], const int arr2[], int n) {
	std::vector<int> v1(arr1, arr1+n);
	std::vector<int> v2(arr2, arr2+n);
	std::sort(v1.begin(), v1.end());
	std::sort(v2.begin(), v2.end());
	return v1 == v2;
}


int* read_numbers(int* n) {
	static char filename[] = "./numbers.txt";
	FILE* fp = fopen(filename, "r");
	if (!fp) {
		printf("open file '%s' error!\n", filename);
		return NULL;
	}
	fscanf(fp, "%d", n);
	int* buf = (int*)malloc(*n * sizeof(int));
	for (int i = 0, tmp; fscanf(fp, "%d", &tmp) != EOF; ++i) {
		buf[i] = tmp;
	}
	fclose(fp);
	printf("read '%s' data succeed!\n", filename);
	return buf;
}


void show_menu() {
	puts("\n======== Sorting ========");
	puts("- COMMAND");
	puts("    0. show menu");
	puts("    1. view all numbers");
	puts("    2. restore random state");
	puts("    5. init numbers");
	puts("    6. shuffle numbers");
	puts("    7. switch auto-restore");
	puts("    8. read data from file");
	puts("    9. exit (or CTRL + C)");
	puts("- Exchange sorts");
	puts("    10. bubble_sort");
	puts("    11. cocktail_sort");
	puts("    12. quicksort");
	puts("    13. quicksort optimied");
	puts("- Selection sorts");
	puts("    20. selection_sort");
	puts("    21. heapsort");
	puts("- Insertion sorts");
	puts("    30. insertion_sort");
	puts("    31. insertion_sort optimized I");
	puts("    32. insertion_sort optimized II");
	puts("    33. binary_insertion_sort");
	puts("    34. shellsort");
	puts("    35. shellsort gap optimized");
	puts("- Merge sorts");
	puts("    40. merge_sort");
	puts("- Distribution sorts");
	puts("    50. counting_sort");
	puts("    51. radix_sort");
	puts("- Hybrid sorts");
	puts("    60. introsort");
	puts("- Standard library sorts");
	puts("    90. qsort");
	puts("    91. std::partial_sort");
	puts("    92. std::stable_sort");
	puts("    93. std::sort");
	puts("-------------------------");
	printf("%d integers in total\n", _total);
	printf("auto-restore is %s\n", _auto_restore ? "on" : "off");
	puts("=========================");
}


int main(int argc, char* argv[]) {
	int idx;
	char ibuf[128] = {0};
	clock_t time_start, time_end;
	
	// srand((unsigned)time(NULL));
	srand(42); // fixed random number sequence
	show_menu();
	
	_initnum = (int*)malloc(_total * sizeof(int));
	_numbers = (int*)malloc(_total * sizeof(int));
	for (int i = 0; i < _total; ++i) {
		_initnum[i] = i;
	}
	shuffle(_initnum, _total);
	memcpy(_numbers, _initnum, sizeof(_initnum[0])*_total);
	
	do {
input:
		printf("AlgoFun> ");
		scanf("%s", ibuf);
		for (int i = 0; i < strlen(ibuf); ++i) {
			if (!isdigit(ibuf[i])) {
				puts("Input is not a number index!");
				goto input;
			}
		}
		idx = atoi(ibuf);
		time_start = clock();
		switch (idx) {
		case 0:
			show_menu();
			break;
		case 1:
			for (int i = 0; i < _total; ++i) {
				printf("%d ", _numbers[i]);
			}
			puts("");
			break;
		case 2:
			memcpy(_numbers, _initnum, sizeof(_initnum[0])*_total);
			printf("There are %d random numbers.\n", _total);
			break;
		case 5:
			printf("How many random numbers you want: ");
			scanf("%d", &_total);
			free(_initnum);
			free(_numbers);
			_initnum = (int*)malloc(_total * sizeof(int));
			_numbers = (int*)malloc(_total * sizeof(int));
			for (int i = 0; i < _total; ++i) {
				_initnum[i] = i;
			}
			shuffle(_initnum, _total);
			memcpy(_numbers, _initnum, sizeof(_initnum[0])*_total);
			break;
		case 6:
			shuffle(_initnum, _total);
			memcpy(_numbers, _initnum, sizeof(_initnum[0])*_total);
			printf("All numbers has shuffled.\n");
			break;
		case 7:
			_auto_restore = !_auto_restore;
			printf("Auto-restore is turn %s\n", _auto_restore ? "on" : "off");
			break;
		case 8: {
			int* buf = read_numbers(&_total);
			free(_initnum);
			free(_numbers);
			_initnum = buf;
			memcpy(_numbers, _initnum, sizeof(_initnum[0])*_total);
			printf("There are %d random numbers.\n", _total);
			break;
		}
		case 9:
			puts("See you :)");
			goto over;
		case 10:
			bubble_sort(_numbers, _total);
			break;
		case 11:
			cocktail_sort(_numbers, _total);
			break;
		case 12:
			quicksort(_numbers, _total);
			break;
		case 13:
			quicksort1(_numbers, _total);
			break;
		case 20:
			selection_sort(_numbers, _total);
			break;
		case 21:
			puts("\ndoing...\n");
			break;
		case 30:
			insertion_sort(_numbers, _total);
			break;
		case 31:
			insertion_sort_1(_numbers, _total);
			break;
		case 32:
			insertion_sort_2(_numbers, _total);
			break;
		case 33:
			binary_insertion_sort(_numbers, _total);
			break;
		case 34:
			shellsort(_numbers, _total);
			break;
		case 35:
			shellsort_1(_numbers, _total);
			break;
		case 40:
			merge_sort(_numbers, _total);
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
		case 90:
			qsort(_numbers, _total, sizeof(_numbers[0]), cmp_int);
			break;
		case 91:
			std::partial_sort(_numbers, _numbers + _total, _numbers + _total);
			break;
		case 92:
			std::stable_sort(_numbers, _numbers + _total);
			break;
		case 93:
			std::sort(_numbers, _numbers + _total);
			break;
		default:
			puts("Input error, please try again.");
			goto input;
		}
		time_end = clock();
		printf("Cost time: %lf second.\n", difftime(time_end, time_start)/CLOCKS_PER_SEC);
		if (idx > 9) {
			if (same_collection(_numbers, _initnum, _total)) {
				if (ordered(_numbers, _total)) {
					puts("Sort succeed !");
				} else {
					puts("Sort failed !");
				}
			} else {
				puts("Sort error: value changed !");
			}
			if (_auto_restore) {
				memcpy(_numbers, _initnum, sizeof(_initnum[0])*_total);
				puts("Numbers restored to initial random state.");
			}
		}
	} while (true);
	free(_initnum);
	free(_numbers);
over:
	return 0;
}
