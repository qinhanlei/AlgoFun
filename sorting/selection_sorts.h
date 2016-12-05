#ifndef _ALGOFUN_SELECTION_SORTS_H
#define _ALGOFUN_SELECTION_SORTS_H

#include <stddef.h>


void selection_sort(void *base, size_t num, size_t size, 
				 int (*cmp_func)(const void*, const void*));


void _heapsort(void *base, size_t num, size_t size, 
			   int (*cmp_func)(const void*, const void*));


#endif //_ALGOFUN_SELECTION_SORTS_H