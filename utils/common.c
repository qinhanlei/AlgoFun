#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


unsigned int bigrand() {
	return RAND_MAX * rand() + rand();
}


int randint(int a, int b) {
	return a + bigrand() % (b - a);
}


void shuffle(int arr[], int n) {
	int i, k;
	for (i = 1; i < n; ++i) {
		swap(arr, i, rand() % (i + 1));
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


void swap(int arr[], int i, int j) {
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}
