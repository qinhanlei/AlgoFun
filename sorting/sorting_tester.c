
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "bubble_sort.h"
#include "select_sort.h"

#define MAX_INPUT 10
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
	printf("got %d numbers from file.\n", total);
	return 1;
}

int cmp_int(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

int main(int argc, char *argv[])
{
	int i, index;

	char is_quit = 0;
	char input_str[64] = {0};
	int input_len = 0;

	clock_t time_start, time_end;

	if (!read_data()) {
		return 0;
	}
	memcpy(num_buf, num_input, sizeof(num_input[0])*total);

	while (1) {
		puts("\n************* Sorting *************");
		puts("\t0.restore random state.");
		puts("\t1.view all numbers\n");

		puts("\t2.bubble_sort");
		puts("\t3.select_sort");
		puts("\t4.insert_sort\n");

		puts("\t5.shell_sort");
		puts("\t6.heap_sort");
		puts("\t7.merge_sort\n");

		puts("\t8.quick_sort");
		puts("\t9.qsort -- C std");

		puts("\n\t99.Exit");
		puts("***********************************");
		printf("\tSelect (0~10): ");

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
			{
				memcpy(num_buf, num_input, sizeof(num_input[0])*total);
				printf("\nthere are %d random numbers.\n", total);
				break;
			}
		case 1:
			{
				print_array(num_buf, total);
				break;
			}
		case 2:
			{
				bubble_sort(num_buf, total, sizeof(num_buf[0]), cmp_int);
				break;
			}
		case 3:
			{
				select_sort(num_buf, total, sizeof(num_buf[0]), cmp_int);
				break;
			}
		case 99:
			{
				is_quit = 1;
				break;
			}
		default:
			{
				printf("\nDoing... or Wrong input !!");
				continue;
			}
		}
		time_end = clock();

		if (is_quit) {
			puts("see you :)");
			break;
		}

		// is that sort operate
		if (index >= 2 && index <= 9) {
			if (is_ordered(num_buf, total)) 
				printf("\nSort successed. ");
			else 
				printf("\nSort unsuccess!!!. ");
			printf("\ncost time: %lf second \n", difftime(time_end, time_start)/CLK_TCK);
		}
	}
	system("pause");
	return 0;
}