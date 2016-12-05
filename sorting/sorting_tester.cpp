
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>
using namespace std;


const int MAX_CMD_INPUT = 64;
const int MAX_NUM = 2000000;

int _total = 0;
int _num_init[MAX_NUM] = {0};
int _numbers[MAX_NUM] = {0};


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


int is_ordered(int arr[], size_t n) {
	size_t i;
	for (i = 0; i < n - 1; ++i) {
		if (arr[i] > arr[i + 1]) {
			return 0;
		}
	}
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
	char input_str[MAX_CMD_INPUT] = {0};
	int auto_restore = 1;
	clock_t time_start, time_end;

	if (!read_data()) {
		return 0;
	}
	memcpy(_numbers, _num_init, sizeof(_num_init[0])*_total);

	do {
		puts("==============================================");
		printf("             Std Sorting (%d integers)\n", _total);
		puts("----------------------------------------------");
		puts("              10. qsort C std");
		puts("              11. sort C++ STL");
		puts("              12. stable_sort C++ STL");
		puts("              13. heap_sort C++ STL");
		puts("----------------------------------------------");
		puts("              0. restore random state.");
		puts("              1. view all numbers");
		puts("              7. switch auto-restore");
		puts("              8. re-read data from file");
		puts("              9. exit");
		puts("==============================================");
		printf("\tauto-restore is %s\n", auto_restore ? "on" : "off");
		printf("\tinput index number: ");

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
			qsort(_numbers, _total, sizeof(_numbers[0]), cmp_int);
			break;
		case 11:
			sort(_numbers, _numbers + _total);
			break;
		case 12:
			stable_sort(_numbers, _numbers + _total);
			break;
		case 13:
			make_heap(_numbers, _numbers + _total);
			sort_heap(_numbers, _numbers + _total);
			break;
		case 0:
			memcpy(_numbers, _num_init, sizeof(_num_init[0])*_total);
			printf("\nthere are %d random numbers.\n", _total);
			break;
		case 1:
			print_array(_numbers, _total);
			break;
		case 7:
			auto_restore = !auto_restore;
			printf("\nauto-restore: %s\n", auto_restore ? "on" : "off");
			break;
		case 8:
			read_data();
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

		if (index > 9 && index <= 90) {
		    if(is_ordered(_numbers, _total)) {
				puts("\nsort success.");
			} else {
				puts("\nsort failed!");
			}
			printf("cost time: %lf second \n\n", difftime(time_end, time_start)/CLOCKS_PER_SEC);
			if (auto_restore) {
				memcpy(_numbers, _num_init, sizeof(_num_init[0])*_total);
				puts("numbers has restored to initial random state.");
			}
		}
	} while (1);
	
over:
	return 0;
}
