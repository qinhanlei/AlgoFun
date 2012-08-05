#include "select_sort.h"

#include "common.h"

void select_sort(void *base, size_t num, size_t size,
				 int (*com_func)(const void*, const void*))
{
	char *ch_base = (char*)base;
	void *a = NULL, *b = NULL;
	size_t i, j;
	for (i = 0; i < num; ++i) {
		a = ch_base + i * size;
		for (j = i + 1; j < num; ++j) {
			b = ch_base + j * size;
			if (com_func(b, a) < 0) {
				// point to minimal element
				a = b;
			}
		}
		b = ch_base + i * size;
		if (a != b) generic_swap(a, b, size);
	}
}