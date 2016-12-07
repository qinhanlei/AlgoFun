#include "selection_sorts.h"

#include "common.h"


void generic_selection_sort(void *base, size_t num, size_t size,
				 int (*com_func)(const void*, const void*)) {
	char *ch_base = base;
	char *a = NULL, *b = NULL;
	size_t i, j;
	for (i = 0; i < num; ++i) {
		a = ch_base + i * size;
		for (j = i + 1; j < num; ++j) {
			b = ch_base + j * size;
			if (com_func(b, a) < 0)
				a = b; // point to minimum element
		}
		b = ch_base + i * size;
		if (a != b) generic_swap(a, b, size);
	}
}


void selection_sort(int arr[], int n) {
	int i, j, k;
	for (i = 0; i < n; ++i) {
		k = i;
		for (j = i + 1; j < n; ++j) {
			if (arr[j] < arr[k]) {
				k = j;
			}
		}
		if (k != i) int_swap(arr+k, arr+i);
	}
}


void heapsort_(int arr[], int n) {
	//TODO: ...
}
