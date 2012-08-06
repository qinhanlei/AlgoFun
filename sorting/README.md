Sorting
=======
At first I want use C++ create a generic sorting lib, but STL works well and I am inexpertness at C++ template programming. so I decide use C do some thing I have never done.  

All sorting funciton is use like C standard library function \"qsort(...)\".

for example:   
        
    int a[MAX_NUM] = {0};
    // ... do some thing initialize entire array 'a[]'.
    // sort entire array
    insert_sort(a, MAX_NUM, sizeof(a[0]), cmp_int);

here, cmp\_int is a function which function prototype like below:  
`int cmp_int(const void*, const void*);`

Note 
----
I delete the file "random\_num.txt" (cause it may changed frequently) you can generate it use "gen\_random\_num2file.c" or manunally.
