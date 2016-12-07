#include "selection_sorts.h"
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


void shellsort_1(void *base, size_t num, size_t size,
				  int (*cmp_func)(const void*, const void*))
{
	char *ch_base = base;
	char *a = NULL, *b = NULL;
	size_t i, gap;
	int j; //note: (j -= gap) may let unsigned j overflow
	// loop gap, let global looks orderly
	for (gap = num / 2; gap > 0; gap /= 2) {
		// like bubble sort below, made slow. :(
		for (i = gap; i < num; ++i) {
			a = ch_base + i * size; // current
			for (j = i - gap; j >= 0; j -= gap) {
				b = ch_base + j * size; // preceding
				if (cmp_func(a, b) < 0) generic_swap(a, b, size);
				a = b;
			}
		}
	}
}


void shellsort_2(void *base, size_t num, size_t size,
				int (*cmp_func)(const void*, const void*)) {
	char *ch_base = base;
	char *a = NULL, *b = NULL;
	size_t i, gap;
	int j; //notice: j-gap may less than zero
	char *tmp = malloc(size);
	if (tmp == NULL) return;
	// loop gap, let global looks orderly
	for (gap = num / 2; gap > 0; gap /= 2) {
		// insertion sort below, works well. :)
		for (i = gap; i < num; ++i) {
			a = ch_base + i * size; // current
			memcpy(tmp, a, size);
			for (j = i - gap; j >= 0; j -= gap) {
				b = ch_base + j * size;
				if (cmp_func(tmp, b) >= 0) break;
				memcpy(a, b, size);
				a = b;
			}
			if (i != j + gap) memcpy(a, tmp, size);
		}
	}
	free(tmp);
}


void binary_shellsort(void *base, size_t num, size_t size,
					   int (*cmp_func)(const void*, const void*)) {
	char *ch_base = base;
	char *a = NULL, *b = NULL;
	size_t i, gap, t;
	int j, left, right, mid;
	char *tmp = malloc(size);
	if (tmp == NULL) return;
	// loop gap, let global looks orderly
	for (gap = num / 2; gap > 0; gap /= 2) {
		for (i = gap; i < num; ++i) {
			memcpy(tmp, ch_base + i * size, size);
			left = i % gap; // notice!
			right = i - gap;
			while (left <= right) {
				// shrink to no gap, binary, and back
				t = (right - left) / gap + 1;
				mid = t / 2 * gap + left;
				a = ch_base + mid * size;
				if (cmp_func(tmp, a) >= 0) left = mid + gap;
				else right = mid - gap;
			}
			/*
			a = ch_base + left * size;
			b = ch_base + i * size;
			while (b >= a) {
				memcpy(b, b - gap * size, size);
				b -= gap * size;
			}
			if (b != ch_base + i * size)
				memcpy(b + gap * size, tmp, size);//*/
			a = ch_base + i * size;
			for (j = i - gap; j >= left; j -= gap) {
				b = ch_base + j * size;
				memcpy(a, b, size);
				a = b;
			}
			if (i != j + gap) memcpy(a, tmp, size);//*/
		}
	}
	free(tmp);
}
