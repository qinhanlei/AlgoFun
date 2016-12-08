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


int bigrand() {
    return RAND_MAX * rand() + rand();
}


int randint(int a, int b) {
    if (a > b)
        return b + bigrand() % (a - b + 1);
    else
        return a + bigrand() % (b - a + 1);
}


void shuffle(int arr[], int n) {
	int i;
	for (i = 1; i < n; ++i) {
        swap(arr[i], arr[rand()%(i+1)]);
	}
}


void print_array(int arr[], int n) {
	int i;
	for (i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	puts("");
}


bool is_ordered(int arr[], int n) {
	int i;
	for (i = 1; i < n; ++i)
		if (arr[i-1] > arr[i])
			return false;
	return true;
}
