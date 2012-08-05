#include "select_sort.h"
#include "common.h"

#include <string.h>
#include <stdlib.h>

void insert_sort(void *base, size_t num, size_t size, 
				 int (*cmp_func)(const void*, const void*))
{
	char *ch_base = (char*)base;
	void *a = NULL, *b = NULL;
	char *tmp = malloc(size);
	if (tmp != NULL) {
		size_t i, j;
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
	}
	free(tmp);
}

void binary_insert_sort( void *base, size_t num, size_t size, int (*cmp_func)(const void*, const void*) )
{
	//TODO:binary_insert_sort
}

