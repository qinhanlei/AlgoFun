#include "common.h"

#include <stdlib.h>
#include <string.h>


// use for reference from Linux kernel source
void generic_swap(void *a, void *b, int size) {
	char *tmp = malloc(size);
	if (tmp == NULL) return;
	memcpy(tmp, a, size);
	memcpy(a, b, size);
	memcpy(b, tmp, size);
	free(tmp);
}


// from programming pearls
int bigrand() {
    return RAND_MAX * rand() + rand();
}


int randint(int a, int b) {
    if (a > b)
        return b + bigrand() % (a - b + 1);
    else
        return a + bigrand() % (b - a + 1);
}
