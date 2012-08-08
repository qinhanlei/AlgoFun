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
// but it is slow (even than insert sort), cause bubble sort.
void shell_sort_1(void *base, size_t num, size_t size, 
				  int (*cmp_func)(const void*, const void*));

// use simple inser sort
void shell_sort(void *base, size_t num, size_t size, 
				int (*cmp_func)(const void*, const void*));

// use binary insert sort. 
// I recommend against this method.
// the binary with gap is complex to code, and inefficiency. :(
void binary_shell_sort(void *base, size_t num, size_t size, 
					   int (*cmp_func)(const void*, const void*));


#endif //_ALGOFUN_INSERTION_SORTS_H