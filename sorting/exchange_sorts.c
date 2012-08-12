#include "exchange_sorts.h"

#include "common.h"

void bubble_sort(void *base, size_t num, size_t size, 
				 int (*cmp_func)(const void*, const void*))
{
	char *ch_base = base;
	char *a = NULL, *b = NULL; // point to adjacent element
	size_t i, j;
	// if no swap, meaning sorted, then interrupt timely
	char is_swapped = 1;
	for (i = 0; i < num - 1 && is_swapped; ++i) {
		is_swapped = 0;
		for (j = 0; j < num - 1 - i; ++j) {
			a = ch_base + j * size;
			b = a + size;
			if (cmp_func(b, a) < 0) {
				generic_swap(a, b, size);
				is_swapped = 1;
			}
		}
	}
}

void cocktail_sort(void *base, size_t num, size_t size, 
				   int (*cmp_func)(const void*, const void*))
{
	char *ch_base = base;
	char *a = NULL, *b = NULL;
	size_t i, front = 0, rear = num - 1;
	// if no swap, meaning sorted, then interrupt timely
	char is_swapped = 1;
	while (is_swapped) {
		is_swapped = 0;
		for (i = front; i < rear; ++i) {
			a = ch_base + i * size;
			b = a + size;
			if (cmp_func(b, a) < 0) {
				generic_swap(a, b, size);
				is_swapped = 1;
			}
		}
		--rear;
		for (i = rear; i > front; --i) {
			b = ch_base + i * size;
			a = b - size;
			if (cmp_func(b, a) < 0) {
				generic_swap(a, b, size);
				is_swapped = 1;
			}
		}
		++front;
	}
}

void quick_sort(void *base, size_t num, size_t size, 
				int (*cmp_func)(const void*, const void*))
{
	//TODO:quick_sort
	base;num;size;cmp_func;
}
