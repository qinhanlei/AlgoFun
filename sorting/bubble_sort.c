#include "bubble_sort.h"

#include "common.h"

void bubble_sort(void *base, size_t num, size_t size, 
				 int (*cmp_func)(const void*, const void*))
{
	size_t i, j;
	// if no swap, meaning sorted, then interrupt timely
	char key = 1;
	for (i = 0; i < num - 1 && key; ++i) {
		key = 0;
		for (j = 0; j < num - 1 - i; ++j) {
			void *a = (char*)base + j * size;
			void *b = (char*)base + (j + 1) * size;
			if (cmp_func(a, b) > 0) {
				generic_swap(a, b, size);
				key = 1;
			}
		}
	}
}
