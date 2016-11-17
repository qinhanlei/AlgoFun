#ifndef _ALGOFUN_MERGE_SORTS_H
#define _ALGOFUN_MERGE_SORTS_H

#include <stddef.h>


void merge_sort(void *base, size_t num, size_t size, 
			   int (*cmp_func)(const void*, const void*));


#endif //_ALGOFUN_MERGE_SORTS_H