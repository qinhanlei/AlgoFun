#include "bubble_sort.h"

#include "common.h"

void bubble_sort(void *base, size_t num, size_t size, 
				 int (*cmp_func)(const void*, const void*))
{
	size_t i, j;
	char *ch_base = (char*)base;
	void *a = NULL, *b = NULL;
	// if no swap, meaning sorted, then interrupt timely
	char key = 1;
	for (i = 0; i < num - 1 && key; ++i) {
		key = 0;
		for (j = 0; j < num - 1 - i; ++j) {
			a = ch_base + j * size;	// element[j]
			b = ch_base + (j + 1) * size; // element[j+1]
			if (cmp_func(a, b) > 0) {
				generic_swap(a, b, size);
				key = 1;
			}
		}
	}
}
