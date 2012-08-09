
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_INPUT = 64;
const int MAX_NUM = 2000000;

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

int main(int argc, char *argv[])
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
		printf("             Std Sorting (%d integers)\n", total);
		puts("----------------------------------------------");
		puts("              10. qsort C std");
		puts("              11. sort C++ STL");
		puts("              12. stable_sort C++ STL");
		puts("              13. heap_sort C++ STL");
		puts("----------------------------------------------");
		puts("              00. restore random state.");
		puts("              01. view all numbers");
		puts("              08. re-read data from file");
		puts("              09. exit");
		puts("==============================================");
		printf("\tinput index number: ");

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
		case 10:
			qsort(num_buf, total, sizeof(num_buf[0]), cmp_int);
			break;
		case 11:
			sort(num_buf, num_buf + total);
			break;
		case 12:
			stable_sort(num_buf, num_buf + total);
			break;
		case 13:
			make_heap(num_buf, num_buf + total);
			sort_heap(num_buf, num_buf + total);
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
		    if(is_ordered(num_buf, total))
                puts("\nsort success.");
            else
                puts("\nsort failed!");
			printf("\ncost time: %lf second \n", difftime(time_end, time_start)/CLK_TCK);
		}
        system("pause");
		system("cls");
	} while (!is_quit);
	return 0;
}
