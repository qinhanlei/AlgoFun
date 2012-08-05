#ifndef _ALGOFUN_SHELL_SORT_H
#define _ALGOFUN_SHELL_SORT_H

#include <stddef.h>

void shell_sort(void *base, size_t num, size_t size, 
			   int (*cmp_func)(const void*, const void*));


#endif //_ALGOFUN_SHELL_SORT_H