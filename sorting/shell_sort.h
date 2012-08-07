#ifndef _ALGOFUN_SHELL_SORT_H
#define _ALGOFUN_SHELL_SORT_H

#include <stddef.h>

// simple implement 
// first as the code at "The C++ Programming Language", 
// but never mind, bubble sort is boring.
void shell_sort_1(void *base, size_t num, size_t size, 
			   int (*cmp_func)(const void*, const void*));

void shell_sort(void *base, size_t num, size_t size, 
				int (*cmp_func)(const void*, const void*));


#endif //_ALGOFUN_SHELL_SORT_H