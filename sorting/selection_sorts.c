#include "selection_sorts.h"

#include "common.h"


void select_sort(void *base, size_t num, size_t size,
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


void heap_sort(void *base, size_t num, size_t size, 
			   int (*cmp_func)(const void*, const void*)) {
	//TODO: ...
}
