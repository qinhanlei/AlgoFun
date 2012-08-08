#ifndef _ALGOFUN_HYBRID_SORTS_H
#define _ALGOFUN_HYBRID_SORTS_H

#include <stddef.h>

// introspective sort, need heap sort
// PS: most C++ STL implement version's sort() is like this.
void intro_sort(void *base, size_t num, size_t size, 
				 int (*cmp_func)(const void*, const void*));

#endif //_ALGOFUN_HYBRID_SORTS_H