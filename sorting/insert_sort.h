#ifndef _ALGOFUN_INSERT_SORT_H
#define _ALGOFUN_INSERT_SORT_H

#include <stddef.h>

void insert_sort(void *base, size_t num, size_t size, 
				 int (*cmp_func)(const void*, const void*));

// binary optimized
void binary_insert_sort(void *base, size_t num, size_t size, 
				 int (*cmp_func)(const void*, const void*));

#endif //_ALGOFUN_INSERT_SORT_H