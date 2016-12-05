#ifndef _ALGOFUN_EXCHANGE_SORTS_H
#define _ALGOFUN_EXCHANGE_SORTS_H

#include <stddef.h>


void bubble_sort(void *base, size_t num, size_t size, 
				 int (*cmp_func)(const void*, const void*));


// a variant of bubble sort (double side bubble)
// almost no efficiency improvement
void cocktail_sort(void *base, size_t num, size_t size, 
				   int (*cmp_func)(const void*, const void*));


void quicksort(void *base, size_t num, size_t size, 
				int (*cmp_func)(const void*, const void*));


#endif //_ALGOFUN_EXCHANGE_SORTS_H