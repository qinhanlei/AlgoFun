#include "shell_sort.h"
#include "common.h"

#include <string.h>
#include <stdlib.h>

void shell_sort_1(void *base, size_t num, size_t size, 
				int (*cmp_func)(const void*, const void*))
{
	char *ch_base = base;
	char *a = NULL, *b = NULL;
	size_t i, j, gap;
	// loop gap, let global looks orderly
	for (gap = num / 2; gap > 0; gap /= 2) {
		// like bubble sort below, made slow. :(
		for (i = gap; i < num; ++i) {
			for (j = i - gap; /*j >= 0*/; j -= gap) {
				a = ch_base + j * size; // current
				b = a + gap * size; // after
				if (cmp_func(b, a) < 0) {
					generic_swap(a, b, size);
				}
				//note: (j -= gap) may let unsigned j overflow
				if (j < gap) break;
			}
		}
	}
}

void shell_sort(void *base, size_t num, size_t size, 
				int (*cmp_func)(const void*, const void*))
{
	char *ch_base = base;
	char *a = NULL, *b = NULL;
	size_t i, j, gap;
	char *tmp = malloc(size);
	if (tmp == NULL) return;
	// loop gap, let global looks orderly
	for (gap = num / 2; gap > 0; gap /= 2) {
		// like bubble sort below, made slow. :(
		for (i = gap; i < num; ++i) {
			a = ch_base + i * size; // current
			memcpy(tmp, a, size);
			for (j = i - gap; j >= 0; j -= gap) {
				b = ch_base + j * size;
				if (cmp_func(tmp, b) < 0) {
					memcpy(a, b, size);
					a = b;
				} else 
					break;
				//note: (j -= gap) may let unsigned j overflow
				if (j < gap) break;
			}
			if (i != j) memcpy(a, tmp, size);
		}
	}
}