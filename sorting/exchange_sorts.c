#include "exchange_sorts.h"

#include "common.h"
#include "insertion_sorts.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


void bubble_sort(int arr[], int n) {
	int i, j;
	bool swapped = true;
	for (i = 0; i < n - 1 && swapped; ++i) {
		swapped = false;
		for (j = 0; j < n - 1 - i; ++j) {
			if (arr[j] > arr[j+1]) {
				swap(arr+j, arr+j+1);
				swapped = true;
			}
		}
	}
}


void cocktail_sort(int arr[], int n) {
	int i, front = 0, rear = n - 1;
	bool swapped = true;
	while (swapped) {
		swapped = false;
		for (i = front; i < rear; ++i) {
			if (arr[i] > arr[i+1]) {
				swap(arr+i, arr+i+1);
				swapped = true;
			}
		}
		--rear;
		for (i = rear; i > front; --i) {
			if (arr[i-1] > arr[i]) {
				swap(arr+i-1, arr+i);
				swapped = true;
			}
		}
		++front;
	}
}


// simplest qsort from "programming pearls" and CLRS
static void _quicksort(int arr[], int left, int right) {
	if (left < right) {
		int i, m = left, pivot = arr[left];
		for (i = left + 1; i < right; ++i) {
			if (arr[i] < pivot) {
				swap(&arr[i], &arr[++m]);
			}
		}
		swap(arr+left, arr+m);
		_quicksort(arr, left, m);
		_quicksort(arr, m + 1, right);
	}
}

void quicksort(int arr[], int n) {
	_quicksort(arr, 0, n);
}


static int _median(int arr[], int left, int right) {
	int a = arr[left], b = arr[(left+right)/2], c = arr[right-1];
	if (a < b) {
		if (b < c) return (left+right)/2;
		if (a < c) return right-1;
		return left;
	}
	if (a < c)
		return left;
	if (b < c)
		return right-1;
	return (left+right)/2;
}

static int _cut_off = 16;
static void _quicksort1(int arr[], int left, int right) {
	if (left + _cut_off < right) {
		int i = left, j = right, pivot;
		swap(arr+left, arr+_median(arr, left, right));
		pivot = arr[left];
		while (true) {
			do ++i;
			while (i < right && arr[i] < pivot);
			do --j;
			while (arr[j] > pivot); // index guaranteed by pivot
			if (i >= j) break;
			swap(arr+i, arr+j);
		}
		swap(arr+left, arr+j);
		_quicksort1(arr, left, j);
		_quicksort1(arr, j + 1, right);
	}
}

void quicksort1(int arr[], int n) {
	_quicksort1(arr, 0, n);
	insertion_sort(arr, n);
}
