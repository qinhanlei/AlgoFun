Sorting
=======
At first I want use C++ create a generic sorting lib, but STL works well and I am inexpertness at C++ template programming. so I decide use C do some thing I have never done.  

Most of sorting funciton is use like C standard library function qsort, below:   
`void qsort(void *buf, size_t num, size_t size, int (*compare)(const void *, const void *));`

For example:   
        
    int a[MAX_NUM] = {0};
    // ... do some thing initialize entire array 'a[]'.
    // sort entire array
    insert_sort(a, MAX_NUM, sizeof(a[0]), cmp_int);

Here, cmp\_int is a function which function prototype like below:  
`int cmp_int(const void*, const void*);` create it according to your own will.

Note 
----
I delete the file "random\_num.txt" (cause it may changed frequently) you can generate it use "gen\_random\_num2file.c" or manunally.
I usually write comment by C++ style "//", so do I in C code. it may got error in some old C compiler, sorry for the inconvenience.
In practice, the std qsort() is recommended in C, and the sort() or stable_sort() in C++.
