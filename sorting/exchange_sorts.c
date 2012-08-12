#include "exchange_sorts.h"

#include "common.h"
#include "insertion_sorts.h"

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

const size_t CUT_OFF = 20;

// the simplest qsort like qsort1 from "programming pearls", and CLRS
void qsort_1(void *base, size_t left, size_t right, size_t size,
			 int (*cmp_func)(const void*, const void*))
{
	if (right > CUT_OFF + left) {
		char *ch_base = base;
		char *a = NULL, *b = ch_base + left * size;
		char *pivot = b;
		size_t i, m = left;
		for (i = left + 1; i <= right; ++i) {
			a = ch_base + i * size;
			if (cmp_func(a, pivot) < 0) {
				++m;
				b += size;
				generic_swap(b, a, size);
			}
		}
		generic_swap(b, pivot, size);
		if (m > 0) 
			qsort_1(base, left, m - 1, size, cmp_func);
		qsort_1(base, m + 1, right, size, cmp_func);
	} /*else {
		insert_sort((char*)base + left * size, right - left + 1, size, cmp_func);
	}*/
}

// little improve
void qsort_2(void *base, size_t left, size_t right, size_t size,
			 int (*cmp_func)(const void*, const void*))
{
	if (right > CUT_OFF + left) {
		char *ch_base = base;
		char *a = ch_base + left * size, *b = ch_base + right * size;
		char *pivot = a, *pright = b;
		size_t j = 0;//i = left, j = right + 1;
		do {
			do {
				//++i;
				a += size;
			} while(a <= pright && cmp_func(a, pivot) < 0);
			do {
				//--j;
				b -= size;
			} while(cmp_func(b, pivot) > 0);
			if (a > b) break;
			generic_swap(a, b, size);
		} while (a < b);
		generic_swap(pivot, b, size);
		j = (b - ch_base) / size;
		if (j > 0) 
			qsort_2(base, left, j - 1, size, cmp_func);
		qsort_2(base, j + 1, right, size, cmp_func);
	}
}

void quick_sort(void *base, size_t num, size_t size, 
				int (*cmp_func)(const void*, const void*))
{
	qsort_2(base, 0, num - 1, size, cmp_func);
	if (CUT_OFF > 0) {
		insert_sort(base, num, size, cmp_func);
		//binary_insert_sort(base, num, size, cmp_func);
	}
}
