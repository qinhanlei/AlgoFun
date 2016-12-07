
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>
using namespace std;

#include "common.h"


const int MAX_CMD_INPUT = 64;
const int MAX_NUM = 2000000;

int _total = 20000;
int _num_init[MAX_NUM] = {0};
int _numbers[MAX_NUM] = {0};

int _auto_restore = 1;


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
	memcpy(_numbers, _num_init, sizeof(_num_init[0])*_total);
	fclose(fp);
	return 1;
}


void init_data() {
	int i;
	for (i = 0; i < _total; ++i) {
		_num_init[i] = i;
	}
	shuffle(_num_init, _total);
	memcpy(_numbers, _num_init, sizeof(_num_init[0])*_total);
}


void show_menu() {
	puts("==============================================");
	printf("             Std Sorting (%d integers)\n", _total);
	puts("----------------------------------------------");
	puts("              10. qsort C std");
	puts("              11. sort C++ STL");
	puts("              12. stable_sort C++ STL");
	puts("              13. heap_sort C++ STL");
	puts("******************* COMMAND *******************");
	puts("              0. show menu");
	puts("              1. view all numbers");
	puts("              2. restore random state.");
	puts("              5. init numbers");
	puts("              6. shuffle numbers");
	puts("              7. switch auto-restore");
	puts("              8. re-read data from file");
	puts("              9. exit");
	puts("==============================================");
	printf("\tauto-restore is %s\n", _auto_restore ? "on" : "off");
}


int main(int argc, char *argv[]) {
	int i;
	int index;
	int input_len = 0;
	char input_str[MAX_CMD_INPUT] = {0};
	clock_t time_start, time_end;

	init_data();
	show_menu();

	do {
input:	printf("AF> ");
		scanf("%d", &index);

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
			show_menu();
			break;
		case 1:
			print_array(_numbers, _total);
			break;
		case 2:
			memcpy(_numbers, _num_init, sizeof(_num_init[0])*_total);
			printf("There are %d random numbers.\n", _total);
			break;
		case 5:
			printf("How many random numbers you want:");
			scanf("%d", &_total);
			init_data();
			break;
		case 6:
			shuffle(_num_init, _total);
			memcpy(_numbers, _num_init, sizeof(_num_init[0])*_total);
			printf("All numbers has shuffled.\n");
			break;
		case 7:
			_auto_restore = !_auto_restore;
			printf("Auto-restore is turn %s\n", _auto_restore ? "on" : "off");
			break;
		case 8:
			read_data();
			printf("There are %d random numbers.\n", _total);
			break;
		case 9:
			puts("See you :)");
			goto over;
		default:
			puts("input error, please try again.");
			goto input;
		}
		time_end = clock();

		if (index > 9) {
			printf("Cost time: %lf second \n", difftime(time_end, time_start)/CLOCKS_PER_SEC);
		    if(is_ordered(_numbers, _total)) {
				puts("Sort success.");
			} else {
				puts("Sort failed!");
			}
			if (_auto_restore) {
				memcpy(_numbers, _num_init, sizeof(_num_init[0])*_total);
				puts("numbers has restored to initial random state.");
			}
		}
	} while (1);
	
over:
	return 0;
}
