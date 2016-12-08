#include "merge_sorts.h"
#include "common.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static int* _tmp;


static void _merge_sort(int arr[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		_merge_sort(arr, left, mid);
		_merge_sort(arr, mid + 1, right);
		int i = left, j = mid + 1, k = left;
		for (; i <= mid && j <= right; ++k) {
			if (arr[i] <= arr[j]) {
				_tmp[k] = arr[i++];
			} else {
				// inverse number: inum += mid - i + 1;
				_tmp[k] = arr[j++];
			}
		}
		while (i <= mid) _tmp[k++] = arr[i++];
		while (j <= right) _tmp[k++] = arr[j++];
		memcpy(arr+left, _tmp+left, (right-left+1)*sizeof(int));
	}
}


void merge_sort(int arr[], int n) {
	_tmp = malloc(n * sizeof(int));
	if (_tmp == NULL) {
		perror("malloc()");
		return;
	}
	_merge_sort(arr, 0, n - 1); //TODO: let it be [0, n), not [0, n-1]
	free(_tmp);
}


static void _merge_sort_inplace(int arr[], int left, int right) {
	if (left + 1 < right) {
		int mid = (left + right) / 2;
		_merge_sort_inplace(arr, left, mid);
		_merge_sort_inplace(arr, mid, right);
		int i = left, j = mid + 1, k = left;
		//TODO: merge it
	}
}


void merge_sort_inplace(int arr[], int n) {
	_merge_sort_inplace(arr, 0, n);
}
