#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void qsort(
    void *buf,
    size_t num,
    size_t size,
    int (*compare)(void const *, void const *)
);

int int_compare(void const* x, void const* y)
{
    int m, n;
    m = *((int *)x);
    n = *((int *)y);

    if(m==n)  return 0;
    return m > n ? 1 : -1;
}

void main()
{
    int a[20], n;
    /*input an array of number*/
    /*call qsort*/
    clock_t start, end;
    start = clock();
    qsort(a, n, sizeof(int), int_compare);
    end = clock();
    printf("Sorting time is: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}
