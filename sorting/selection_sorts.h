#ifndef _ALGOFUN_SELECTION_SORTS_H
#define _ALGOFUN_SELECTION_SORTS_H

#include <stddef.h>


void generic_selection_sort(void *base, size_t num, size_t size,
				 int (*cmp_func)(const void*, const void*));
void selection_sort(int arr[], size_t n);


void heapsort_(int arr[], size_t n);


#endif //_ALGOFUN_SELECTION_SORTS_H
