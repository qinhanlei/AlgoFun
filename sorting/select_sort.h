#ifndef _ALGOFUN_SELECT_SORT_H
#define _ALGOFUN_SELECT_SORT_H

#include <stddef.h>

void select_sort(void *base, size_t num, size_t size, 
				 int (*cmp_func)(const void*, const void*));


#endif //_ALGOFUN_SELECT_SORT_H