#ifndef _ALGOFUN_INSERTION_SORTS_H
#define _ALGOFUN_INSERTION_SORTS_H

#include <stddef.h>


// standard insertion sort
void insertion_sort(int arr[], int n);
// optimize tries
void insertion_sort_1(int arr[], int n);
void insertion_sort_2(int arr[], int n);
// binary optimized
void binary_insertion_sort(int arr[], int n);


void shellsort(int arr[], int n);
// better increment sequence
void shellsort_1(int arr[], int n);


#endif //_ALGOFUN_INSERTION_SORTS_H
