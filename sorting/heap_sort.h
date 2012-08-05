#ifndef _ALGOFUN_HEAP_SORT_H
#define _ALGOFUN_HEAP_SORT_H

#include <stddef.h>

void heap_sort(void *base, size_t num, size_t size, 
				 int (*cmp_func)(const void*, const void*));


#endif //_ALGOFUN_HEAP_SORT_H