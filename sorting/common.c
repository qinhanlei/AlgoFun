#include "common.h"

#include <stdlib.h>
#include <string.h>


void generic_swap(void *a, void *b, int size) {
	char *tmp = malloc(size);
	if (tmp == NULL) return;
	memcpy(tmp, a, size);
	memcpy(a, b, size);
	memcpy(b, tmp, size);
	free(tmp);
}


void int_swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


void shuffle(int arr[], int num) {
	int i;
	for (i = 1; i < num; ++i) {
        int_swap(arr + i, arr + rand()%(i+1));
	}
}


int bigrand() {
    return RAND_MAX * rand() + rand();
}


int randint(int a, int b) {
    if (a > b)
        return b + bigrand() % (a - b + 1);
    else
        return a + bigrand() % (b - a + 1);
}
