#include "selection_sorts.h"

#include "common.h"


void selection_sort(int arr[], int n) {
	int i, j, k;
	for (i = 0; i < n; ++i) {
		k = i;
		for (j = i + 1; j < n; ++j)
			if (arr[j] < arr[k])
				k = j;
		if (k != i)
			swap(arr[k], arr[i]);
	}
}


void heapsort_(int arr[], int n) {
	//TODO: ...
}
