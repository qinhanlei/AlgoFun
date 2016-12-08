#ifndef _ALGOFUN_MERGE_SORTS_H
#define _ALGOFUN_MERGE_SORTS_H

#include <stddef.h>


void generic_merge_sort(void *base, size_t num, size_t size,
			   int (*cmp_func)(const void*, const void*));
void merge_sort(int arr[], int n);


#endif //_ALGOFUN_MERGE_SORTS_H
