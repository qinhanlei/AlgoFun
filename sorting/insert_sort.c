#include "select_sort.h"
#include "common.h"

#include <string.h>
#include <stdlib.h>

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
			while (cmp_func(tmp, a) < 0) { // unguarded while cause EXP
				a -= size;
			}
			memmove(a + 2 * size, a + size, b - a - size);
			memcpy(a + size, tmp, size);//*/
		}
	}
	free(tmp);
}


void binary_insert_sort(void *base, size_t num, size_t size, 
						int (*cmp_func)(const void*, const void*))
{
	//TODO:binary_insert_sort
}

