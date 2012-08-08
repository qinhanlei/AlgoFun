#include "selection_sorts.h"
#include "common.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

void insert_sort_1(void *base, size_t num, size_t size, 
				 int (*cmp_func)(const void*, const void*))
{
	char *ch_base = base;
	void *a = NULL, *b = NULL;
	size_t i, j;
	char *tmp = malloc(size);
	if (tmp == NULL) return;
	for (i = 1; i < num; ++i) {
		a = ch_base + i * size;
		memcpy(tmp, a, size);
		for (j = i; j > 0; --j) {
			b = ch_base + (j - 1) * size;
			if (cmp_func(tmp, b) < 0) {
				// move element[j-1] to element[j]
				memcpy(a, b, size);
				a = b; // record the old point of element[j-1]
			} else
				break;
		}
		if (i != j) memcpy(a, tmp, size);
	}
	free(tmp);
}

// try little optimize
void insert_sort_2(void *base, size_t num, size_t size, 
				 int (*cmp_func)(const void*, const void*))
{
	char *ch_base = base;
	void *a = NULL, *b = NULL;
	size_t i, j;
	char *tmp = malloc(size);
	if (tmp == NULL) return;
	for (i = 1; i < num; ++i) {
		// store the [i]th element
		memcpy(tmp, ch_base + i * size, size);
		for (j = i; j > 0; --j) {
			b = ch_base + (j - 1) * size;
			if (cmp_func(tmp, b) >= 0) break;
		}
		if (i != j) {
			a = ch_base + j * size;
			b = ch_base + (j + 1) * size;
			// move just once, may be got better efficiency.
			memmove(b, a, (i - j) * size);
			memcpy(a, tmp, size);
		}
	}
	free(tmp);
}

// inspired by C++ STL source code
void insert_sort(void *base, size_t num, size_t size, 
				 int (*cmp_func)(const void*, const void*))
{
	char *ch_base = base;
	char *a = NULL, *b = NULL;
	size_t i;
	char *tmp = malloc(size);
	if (tmp == NULL) return;
	for (i = 1; i < num; ++i) {
		// store the [i]th element
		memcpy(tmp, ch_base + i * size, size);
		if (cmp_func(tmp, ch_base) < 0) { 
			// less than current minimum, move at once.
			memmove(ch_base + size, ch_base, i * size);
			memcpy(ch_base, tmp, size);
		} else { // cmp_func(tmp, ch_base) >= 0   <=>   EXP
			/*b = ch_base + i * size; // current
			a = b - size; // preceding
			while (cmp_func(tmp, a) < 0) { // unguarded while cause EXP
				memcpy(b, a, size);
				b = a;
				a -= size;
			}
			memcpy(b, tmp, size);//*/
			
			b = ch_base + i * size; // current
			a = b - size; // preceding
			// unguarded while cause EXP, the key of efficiency
			while (cmp_func(tmp, a) < 0)
				a -= size;
			memmove(a + 2 * size, a + size, b - a - size);
			memcpy(a + size, tmp, size);//*/
			/*a += size;
			memmove(a + size, a, b - a);
			memcpy(a, tmp, size);//*/
		}
	}
	free(tmp);
}

void binary_insert_sort(void *base, size_t num, size_t size, 
						int (*cmp_func)(const void*, const void*))
{
	char *ch_base = base;
	char *a = NULL, *b = NULL;
	size_t i, left, right, mid;
	char *tmp = malloc(size);
	if (tmp == NULL) return;
	for (i = 1; i < num; ++i) {
		// store the [i]th element
		memcpy(tmp, ch_base + i * size, size);
		if (cmp_func(tmp, ch_base) < 0) { 
			// less than current minimum, move at once.
			memmove(ch_base + size, ch_base, i * size);
			memcpy(ch_base, tmp, size);
		} else {
			left = 0;
			right = i - 1;
			while (left <= right) {
				mid = (left + right) / 2;
				a = ch_base + mid * size;
				if (cmp_func(tmp, a) >= 0) left = mid + 1;
				else right = mid - 1;
			}
			b = ch_base + i * size; // current
			a = ch_base + left * size;
			memmove(a + size, a, b - a);
			memcpy(a, tmp, size); // move tmp to element[left]
		}
	}
	free(tmp);
}

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
				if (cmp_func(b, a) < 0)
					generic_swap(a, b, size);
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
	size_t i, gap;
	int j; //notice: j-gap may less than zero
	char *tmp = malloc(size);
	if (tmp == NULL) return;
	// loop gap, let global looks orderly
	for (gap = num / 2; gap > 0; gap /= 2) {
		// insertion sort below, works well. :)
		for (i = gap; i < num; ++i) {
			a = ch_base + i * size; // current
			memcpy(tmp, a, size);
			for (j = i - gap; j >= 0; j -= gap) {
				b = ch_base + j * size;
				if (cmp_func(tmp, b) >= 0) break;
				memcpy(a, b, size);
				a = b;
			}
			if (i != j + gap) memcpy(a, tmp, size);
		}
	}
	free(tmp);
}

void binary_shell_sort(void *base, size_t num, size_t size, 
					   int (*cmp_func)(const void*, const void*))
{
	char *ch_base = base;
	char *a = NULL, *b = NULL;
	size_t i, gap, t;
	int j, left, right, mid;
	char *tmp = malloc(size);
	if (tmp == NULL) return;
	// loop gap, let global looks orderly
	for (gap = num / 2; gap > 0; gap /= 2) {
		// insertion sort below, works well. :)
		for (i = gap; i < num; ++i) {
			memcpy(tmp, ch_base + i * size, size);
			left = i % gap; // notice!
			right = i - gap;
			while (left <= right) {
				// shrink to no gap, binary, and back
				t = (right - left) / gap + 1;
				mid = t / 2 * gap + left;
				a = ch_base + mid * size;
				if (cmp_func(tmp, a) >= 0) left = mid + gap;
				else right = mid - gap;
			}
			for (j = i - gap; j >= left; j -= gap) {
				b = ch_base + j * size; // element[j-gap]
				a = b + gap * size; // element[j];
				memcpy(a, b, size);
			}
			if (i != j + gap) {
				//a = ch_base + left * size;
				//memcpy(a, tmp, size);
				//memcpy(ch_base + left * size, tmp, size);
				memcpy(b, tmp, size);
			}
		}
	}
	free(tmp);
}