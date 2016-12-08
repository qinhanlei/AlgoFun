#ifndef _ALGOFUN_COMMON_H
#define _ALGOFUN_COMMON_H

#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#else
#define bool char
#define true  1
#define false 0
#define swap(x, y) {int tmp = (x); (x) = (y); (y) = tmp;}
#endif //__cplusplus


// from Linux kernel source
void generic_swap(void *a, void *b, int size);

// for functions like qsort in stdlib of C
int cmp_int(const void* a, const void* b);


// from programming pearls
int bigrand();
int randint(int a, int b);


void shuffle(int arr[], int n);
void print_array(int arr[], int n);
bool is_ordered(int arr[], int n);


#ifdef __cplusplus
}
#endif //__cplusplus


#endif //_ALGOFUN_COMMON_H
