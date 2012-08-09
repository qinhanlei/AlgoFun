#include "merge_sorts.h"
#include "common.h"

/*
static void merge(void *base, size_t left, size_t mid, size_t right,
				  int (*cmp_func)(const void*, const void*))
{
	//TODO:
}

void merge_sort(void *left, size_t num, size_t size, 
			   int (*cmp_func)(const void*, const void*))
{
	if (num > 1) {
		size_t num1 = num / 2;
		size_t num2 = num - num1;
		char *mid = left + num1 * size;
		char *right = left + num * size;
		merge_sort(left, num1, size, cmp_func);
		merge_sort(mid, num2, size, cmp_func);
		merge(left, mid, right, size, cmp_func);
	}
}//*/

