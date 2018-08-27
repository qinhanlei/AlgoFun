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


void swap(int* a, int* b);

// from programming pearls
unsigned int bigrand();
// pseudo-random number in [a,b)
int randint(int a, int b);

void shuffle(int arr[], int n);
bool ordered(int arr[], int n);


#ifdef __cplusplus
}
#endif //__cplusplus


#endif //_ALGOFUN_COMMON_H
