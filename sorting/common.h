#ifndef _ALGOFUN_COMMON_H
#define _ALGOFUN_COMMON_H

#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#else
#define bool char
#define true  1
#define false 0
#endif //__cplusplus


// from Linux kernel source
void generic_swap(void *a, void *b, int size); //TODO: remove latter



// from programming pearls
unsigned int bigrand();
// pseudo-random number in [a,b)
int randint(int a, int b);


void shuffle(int arr[], int n);
void print_array(int arr[], int n);
bool is_ordered(int arr[], int n);
void swap(int arr[], int i, int j);


#ifdef __cplusplus
}
#endif //__cplusplus


#endif //_ALGOFUN_COMMON_H
