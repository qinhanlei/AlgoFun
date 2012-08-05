#ifndef _ALGOFUN_BUBBLE_SORT_H
#define _ALGOFUN_BUBBLE_SORT_H

#include <stddef.h>

void bubble_sort(void *base, size_t num, size_t size, 
				 int (*cmp_func)(const void*, const void*));

// a variant of bubble sort (double side bubble)
void cocktail_sort(void *base, size_t num, size_t size, 
				 int (*cmp_func)(const void*, const void*));


#endif //_ALGOFUN_BUBBLE_SORT_H