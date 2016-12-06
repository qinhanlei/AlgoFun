#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void generic_swap(void *a, void *b, int size) {
	char *tmp = malloc(size);
	if (tmp == NULL) return;
	memcpy(tmp, a, size);
	memcpy(a, b, size);
	memcpy(b, tmp, size);
	free(tmp);
}


void int_swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


int bigrand() {
    return RAND_MAX * rand() + rand();
}


int randint(int a, int b) {
    if (a > b)
        return b + bigrand() % (a - b + 1);
    else
        return a + bigrand() % (b - a + 1);
}


void shuffle(int arr[], int num) {
	int i;
	for (i = 1; i < num; ++i) {
        int_swap(arr + i, arr + rand()%(i+1));
	}
}


void print_array(int arr[], size_t n) {
	size_t i;
	for (i = 0; i < n; ++i) {
		//if (i % 5 == 0) puts("");
		printf("%d ", arr[i]);
	}
	puts("\n");
}


bool is_ordered(int arr[], size_t n) {
	size_t i;
	for (i = 0; i < n - 1; ++i)
		if (arr[i] > arr[i + 1])
			return false;
	return true;
}
