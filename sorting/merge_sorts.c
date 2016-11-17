#include "merge_sorts.h"
#include "common.h"

#include <string.h>
#include <stdlib.h>


static void _merge(void *tmp, void *base,
				  size_t left, size_t mid, size_t right, size_t size, 
				  int (*cmp_func)(const void*, const void*)) {
	size_t i = left, j = mid + 1, k = left;
	char *ch_base = base, *ch_tmp = tmp;
	char *a = ch_base + i * size, *b = ch_base + j * size;
	char *c = ch_tmp + k * size;
	while (i <= mid && j <= right) {
		if (cmp_func(a, b) <= 0) {
			memcpy(c, a, size);
			++i;
			a += size;
		} else {
			memcpy(c, b, size);
			++j;
			b += size;
		}
		++k;
		c += size;
	}
	while (i <= mid) {
		memcpy(c, a, size);
		++i;
		++k;
		a += size;
		c += size;
	}
	while (j <= right) {
		memcpy(c, b, size);
		++j;
		++k;
		b += size;
		c += size;
	}
	memcpy(ch_base + left * size, ch_tmp + left * size, 
		size * (right - left + 1));
}


static void _merge_sort(void *tmp, void *base, 
						size_t left, size_t right, size_t size,
						int (*cmp_func)(const void*, const void*)) {
	if (left < right) {
		size_t mid = (left + right) / 2;
		_merge_sort(tmp, base, left, mid, size, cmp_func);
		_merge_sort(tmp, base, mid + 1, right, size, cmp_func);
		_merge(tmp, base, left, mid, right, size, cmp_func);
	}
}


void merge_sort(void *base, size_t num, size_t size, 
			   int (*cmp_func)(const void*, const void*)) {
	char *tmp = malloc(num * size);
	if (tmp == NULL) return; // Unhandled exception
	_merge_sort(tmp, base, 0, num - 1, size, cmp_func);
	free(tmp);
}

