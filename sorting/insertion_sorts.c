#include "insertion_sorts.h"
#include "common.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


void insertion_sort(int arr[], int n) {
	int i, j, tmp;
	for (i = 1; i < n; ++i) {
		tmp = arr[i];
		for (j = i-1; j >= 0 && arr[j] > tmp; --j) {
			arr[j+1] = arr[j];
		}
		if (i != j) arr[j+1] = tmp;
	}
}


void insertion_sort_1(int arr[], int n) {
	int i, j, tmp;
	for (i = 1; i < n; ++i) {
		tmp = arr[i];
		for (j = i; j > 0 && arr[j-1] > tmp; --j); // one line loop
		if (i != j) {
			memmove(arr+j+1, arr+j, (i-j) * sizeof(int));
			arr[j] = tmp;
		}
	}
}


// inspired by C++ STL source code
void insertion_sort_2(int arr[], int n) {
	int i, j, tmp;
	for (i = 1; i < n; ++i) {
		tmp = arr[i];
		if (tmp < arr[0]) {
			memmove(arr+1, arr, i * sizeof(int));
			arr[0] = tmp;
		} else {
			for (j = i - 1; tmp < arr[j]; --j); // one line loop
			memmove(arr+j+2, arr+j+1, (i-j-1)*sizeof(int));
			arr[j+1] = tmp;
		}
	}
}


void binary_insertion_sort(int arr[], int n) {
	int i, left, right, mid, tmp;
	for (i = 1; i < n; ++i) {
		tmp = arr[i];
		left = 0;
		right = i - 1;
		while (left <= right) {
			mid = (left + right) / 2;
			if (tmp >= arr[mid]) left = mid + 1;
			else right = mid - 1;
		}
		memmove(arr+left+1, arr+left, (i-left)*sizeof(int));
		arr[left] = tmp;
	}
}


void shellsort(int arr[], int n) {
	int i, j, gap, tmp;
	for (gap = n/2; gap > 0; gap /= 2) {
		for (i = gap; i < n; ++i) {
			tmp = arr[i];
			for (j = i-gap; j >= 0 && arr[j] > tmp; j -= gap) {
				arr[j+gap] = arr[j];
			}
			if (i != j) arr[j+gap] = tmp;
		}
	}
}


// https://en.wikipedia.org/wiki/Shellsort
// O(N^(4/3))	Sedgewick, 1986[6]
// python:  [4**k+3*(2**(k-1))+1 for k in range(1,16)][::-1]+[1]
static int _gaps[] = {
	1073790977, 268460033, 67121153, 16783361, 4197377, 1050113,
	262913, 65921, 16577, 4193, 1073, 281, 77, 23, 8, 1
};
static int _gaps_len = sizeof(_gaps)/sizeof(_gaps[0]);

void shellsort_1(int arr[], int n) {
	int i, j, k, gap, left, right, mid, tmp;
	for (k = 0; k < _gaps_len; ++k) {
		if (_gaps[k] < n) break;
	}
	for (; k < _gaps_len; ++k) {
		gap = _gaps[k];
		for (i = gap; i < n; ++i) {
			tmp = arr[i];
			for (j = i-gap; j >= 0 && arr[j] > tmp; j -= gap) {
				arr[j+gap] = arr[j];
			}
			if (i != j) arr[j+gap] = tmp;
		}
	}
}
