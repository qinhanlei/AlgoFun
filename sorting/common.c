#include "common.h"

#include <stdlib.h>

// use for reference from Linux kernel source
void generic_swap(void *a, void *b, int size)
{
	char tmp, *p = a, *q = b;
	while (size--) {
		tmp = *p;
		*p++ = *q;
		*q++ = tmp;
	}
}


// from programming pearls
int bigrand()
{
    return RAND_MAX * rand() + rand();
}

int randint(int a, int b)
{
    if (a > b)
        return b + bigrand() % (a - b + 1);
    else
        return a + bigrand() % (b - a + 1);
}
