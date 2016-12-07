#ifndef _ALGOFUN_EXCHANGE_SORTS_H
#define _ALGOFUN_EXCHANGE_SORTS_H

#include <stddef.h>


void bubble_sort(int arr[], size_t n);


// a variant of bubble sort (double side bubble)
void cocktail_sort(int arr[], size_t n);


void gneric_quicksort(void *base, size_t num, size_t size,
				int (*cmp_func)(const void*, const void*));
void quicksort(int arr[], size_t n);


#endif //_ALGOFUN_EXCHANGE_SORTS_H
