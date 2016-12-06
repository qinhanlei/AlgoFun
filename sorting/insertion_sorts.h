#ifndef _ALGOFUN_INSERTION_SORTS_H
#define _ALGOFUN_INSERTION_SORTS_H

#include <stddef.h>


void generic_insertion_sort(void *base, size_t num, size_t size, 
				 int (*cmp_func)(const void*, const void*));
void insertion_sort(int arr[], size_t n);


// binary optimized
void binary_insertion_sort(void *base, size_t num, size_t size, 
						int (*cmp_func)(const void*, const void*));


// simple implement 
// first as the code at "The C++ Programming Language", 
// but it is slow (even more slow than insert sort), 
// cause too many swap operate like bubble sort.
void shellsort_1(void *base, size_t num, size_t size, 
				  int (*cmp_func)(const void*, const void*));


// use simple inser sort
void shellsort_2(void *base, size_t num, size_t size, 
				int (*cmp_func)(const void*, const void*));


// use binary insert sort. 
// I recommend against this method.
// the binary with gap is complex to code, and no more efficient. :(
void binary_shellsort(void *base, size_t num, size_t size, 
					   int (*cmp_func)(const void*, const void*));


//TODO: choice better increment sequence for shell sort


#endif //_ALGOFUN_INSERTION_SORTS_H