#include "merge_sorts.h"
#include "common.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static void merge(int tmp[], int arr[], int left, int mid, int right) {
	int i = left, j = mid + 1, k = left;
	for ( ; i <= mid && j <= right; ++k) {
		if (arr[i] <= arr[j]) {
			tmp[k] = arr[i++];
		} else {
			// inverse number: inum += mid - i + 1;
			tmp[k] = arr[j++];
		}
	}
	while (i <= mid) {
		tmp[k++] = arr[i++];
	}
	while (j <= right) {
		tmp[k++] = arr[j++];
	}
	memcpy(arr+left, tmp+left, (right-left+1)*sizeof(int));
}


static void merge_sort_(int tmp[], int arr[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		merge_sort_(tmp, arr, left, mid);
		merge_sort_(tmp, arr, mid + 1, right);
		merge(tmp, arr, left, mid, right);
	}
}


void merge_sort(int arr[], int n) {
	int *tmp = malloc(n * sizeof(int));
	if (tmp == NULL) {
		perror("malloc()");
		return;
	}
	merge_sort_(tmp, arr, 0, n - 1);
	free(tmp);
}
