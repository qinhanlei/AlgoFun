#ifndef _ALGOFUN_SORTS_H
#define _ALGOFUN_SORTS_H

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


#include "distribution_sorts.h"
#include "exchange_sorts.h"
#include "hybrid_sorts.h"
#include "insertion_sorts.h"
#include "merge_sorts.h"
#include "selection_sorts.h"


// for functions like qsort in stdlib of C
int cmp_int(const void* a, const void* b);


#ifdef __cplusplus
}
#endif //__cplusplus

#endif //_ALGOFUN_SORTS_H
