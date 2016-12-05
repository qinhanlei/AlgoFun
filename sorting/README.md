# Sorting
At first I want use C++ create a generic sorting lib, but STL works well and I am inexpertness at C++ template programming. 
So I decide use C do some thing I have never done.  

Most of sorting funciton is use like C standard library function qsort, below:
```
void qsort(void *buf, size_t num, size_t size, int (*compare)(const void *, const void *));
```

For example:
```c
    int a[MAX_NUM] = {0};
    // ... do some thing initialize entire array 'a[]'.
    // sort entire array
    insert_sort(a, MAX_NUM, sizeof(a[0]), cmp_int);
```

Here, `cmp_int` is a function which prototype like `int cmp_int(const void*, const void*);`, create it according to your own will.

## Note
* I delete the file `random_num.txt` (cause it may changed frequently) you can generate it use `gen_random_num.c` or manunally.  
* I usually write comment by C++ style `//`, so do I in C code. it may got error in some old C compiler, sorry for the inconvenience.  
* In practice, the std qsort() is recommended in C, and the sort() or stable_sort() in C++.
