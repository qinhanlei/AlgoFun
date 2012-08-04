#ifndef _ALGOFUN_COMMON_H
#define _ALGOFUN_COMMON_H

#include <stdlib.h>

// use for reference from Linux kernel source
inline void generic_swap(void *a, void *b, int size)
{
	char tmp, *p = (char *)a, *q = (char *)b;
	while (size--) {
		tmp = *p;
		*p++ = *q;
		*q++ = tmp;
	}
}


// from programming pearls
inline int bigrand()
{
    return RAND_MAX * rand() + rand();
}

inline int randint(int a, int b)
{
    if (a > b)
        return b + bigrand() % (a - b + 1);
    else 
        return a + bigrand() % (b - a + 1);
}


#endif //_ALGOFUN_COMMON_H
