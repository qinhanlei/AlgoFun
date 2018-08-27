#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


unsigned int bigrand() {
	return RAND_MAX * rand() + rand();
}


int randint(int a, int b) {
	return a + bigrand() % (b - a);
}


void shuffle(int arr[], int n) {
	int i, k;
	for (i = 1; i < n; ++i) {
		swap(arr+i, arr+rand()%(i+1));
	}
}


bool ordered(int arr[], int n) {
	int i;
	for (i = 1; i < n; ++i)
		if (arr[i-1] > arr[i])
			return false;
	return true;
}
