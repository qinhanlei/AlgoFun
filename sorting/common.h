#ifndef _ALGOFUN_COMMON_H
#define _ALGOFUN_COMMON_H


#ifndef __cplusplus
    #define bool char
    #define true  1
    #define false 0
#endif  


// from Linux kernel source
void generic_swap(void *a, void *b, int size);

void int_swap(int *a, int *b);


void shuffle(int arr[], int num);


// from programming pearls
int bigrand();

int randint(int a, int b);


#endif //_ALGOFUN_COMMON_H
