#include "select_sort.h"
#include "common.h"

#include <string.h>

void insert_sort(void *base, size_t num, size_t size, 
				 int (*cmp_func)(const void*, const void*))
{
	char *ch_base = (char*)base;
	void *a = NULL, *b = NULL;
	size_t i, j;
	for (i = 1; i < num; ++i) {
		a = ch_base + i * size;
		for (j = i; j > 0; --j) {
			b = ch_base + (j - 1) * size;
			if (cmp_func(a, b) >= 0) break;
			// move element[j-1] to element[j]
			memcpy(ch_base + j * size, b, size);
		}
		if (i != j) memcpy(b, a, size);
	}
}

void binary_insert_sort( void *base, size_t num, size_t size, int (*cmp_func)(const void*, const void*) )
{
	//TODO:binary_insert_sort
}

