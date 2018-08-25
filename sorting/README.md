# Sorting

https://en.wikipedia.org/wiki/Sorting_algorithm

## Generic sort implements (**DEPRECATED!**)

At first I want use C++ create a generic sorting lib, but STL works well and I am inexpertness at C++ template programming.

So I decide use C do some thing I have never done.  

Most of sorting function is use like C standard library function qsort, below:
```c
void qsort(void *buf, size_t num, size_t size, int (*compare)(const void *, const void *));
```

For example:
```c
    int a[MAX_NUM] = {0};
    // ... initialize entire array 'a[]' ...
    insertion_sort(a, MAX_NUM, sizeof(a[0]), cmp_int);
```

Here, `cmp_int` is a function which prototype like `int cmp_int(const void*, const void*);`, create it according to your own will.

**NOTE**: deprecated and removed now!


## Simple implements
Just sort for integer array with size as below:
```c
insertion_sort(int arr[], int n)
```


## How to run
- `sh randnum.sh`
- `sh runtest.sh`


## TODO
- distribution sorts
- hybird sorts
- merge sort inplace
- selection sorts
  - heap sort
  - smoothsort
