#ifndef _ALGOFUN_QUICK_SORT_H
#define _ALGOFUN_QUICK_SORT_H

#include <stddef.h>

void quick_sort(void *base, size_t num, size_t size, 
				int (*cmp_func)(const void*, const void*));

// introspective sort, need heap sort
// PS: most C++ STL sort is implement like this.
void intro_sort(void *base, size_t num, size_t size, 
				int (*cmp_func)(const void*, const void*));

#endif //_ALGOFUN_QUICK_SORT_H