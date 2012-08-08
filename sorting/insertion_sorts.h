#ifndef _ALGOFUN_INSERTION_SORTS_H
#define _ALGOFUN_INSERTION_SORTS_H

#include <stddef.h>

void insert_sort(void *base, size_t num, size_t size, 
				 int (*cmp_func)(const void*, const void*));

// binary optimized
void binary_insert_sort(void *base, size_t num, size_t size, 
						int (*cmp_func)(const void*, const void*));


// simple implement 
// first as the code at "The C++ Programming Language", 
// but never mind, bubble sort is boring.
void shell_sort_1(void *base, size_t num, size_t size, 
				  int (*cmp_func)(const void*, const void*));

// use simple inser sort
void shell_sort(void *base, size_t num, size_t size, 
				int (*cmp_func)(const void*, const void*));

// use binary insert sort
void binary_shell_sort(void *base, size_t num, size_t size, 
					   int (*cmp_func)(const void*, const void*));


#endif //_ALGOFUN_INSERTION_SORTS_H