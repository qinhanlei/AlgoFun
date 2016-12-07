# Sorting

## Generic sort implements (\***BAD CHOICE**\* deprecated)

At first I want use C++ create a generic sorting lib, but STL works well and I am inexpertness at C++ template programming.

So I decide use C do some thing I have never done.  

Most of sorting funciton is use like C standard library function qsort, below:
```
void qsort(void *buf, size_t num, size_t size, int (*compare)(const void *, const void *));
```

For example:
```c
    int a[MAX_NUM] = {0};
    // ... initialize entire array 'a[]' ...
    insertion_sort(a, MAX_NUM, sizeof(a[0]), cmp_int);
```

Here, `cmp_int` is a function which prototype like `int cmp_int(const void*, const void*);`, create it according to your own will.


## Simple implements
TODO: ...


## How to run
- Open console or terminal
- `sh ctester.sh` or `sh cpptester.sh`
