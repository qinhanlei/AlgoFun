#include "bubble_sort.h"

#include "common.h"

void bubble_sort(void *base, size_t num, size_t size, 
				 int (*cmp_func)(const void*, const void*))
{
	char *ch_base = base;
	char *a = NULL, *b = NULL;
	size_t i, j;
	// if no swap, meaning sorted, then interrupt timely
	char key = 1;
	for (i = 0; i < num - 1 && key; ++i) {
		key = 0;
		for (j = 0; j < num - 1 - i; ++j) {
			// point to adjacent element
			a = ch_base + j * size;
			b = a + size;
			if (cmp_func(b, a) < 0) {
				generic_swap(a, b, size);
				key = 1;
			}
		}
	}
}

void cocktail_sort(void *base, size_t num, size_t size, 
				   int (*cmp_func)(const void*, const void*))
{
	//TODO:cocktail_sort
}
