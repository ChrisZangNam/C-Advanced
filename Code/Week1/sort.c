#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define HUGE_NUMBER 10000000
#define SMALL_NUMBER 20
#include "Sorting.h"
#include <string.h>

void exch(int a[], long i, long j)
{
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}
//Quick_3way
void sort(int a[], int L, int R)
{
    if(R <= L) return;

    int i = L - 1, j = R;
    int p = L - 1, q = R;

    while(1)
    {
        while(a[++i] < a[R]);
        while(a[R] < a[--j])
            if(j==L)
                break;
        if(i >= j)
            break;
        exch(a, i, j);
        if(a[i] == a[R])
            exch(a, ++p, i);
        if(a[j] == a[R])
            exch(a, --q, j);
    }
    exch(a, i, R);
    j = i - 1;
    i = i + 1;
    for (int k = L; k <= p; k++)
        exch(a, k, j--);
    for (int k = R - 1; k >= q; k--)
        exch(a, k, i++);
    sort(a, L, j);
    sort(a, i, R);
}


int* creatArray(long n)
{
    int *a;
    long i;
    a = malloc(sizeof(int) * n);
    srand(time(NULL));
    for (i = 0; i < n; i++)
        a[i] = rand() % 11;

    return a;
}

int* dumpArray(int a[], long n)
{
    int *b;
    long i;
    b = malloc(sizeof(int)*n);
    for (i = 0; i < n; i++)
        b[i] = a[i];

    return b;
}

void printArray(int a[], int n)
{
    for (long i = 0; i < n; i++)
        printf("%d\t", a[i]);
    printf("\n");
}

void qsort(
    void *buf,
    size_t num,
    size_t size,
    int (*compare)(void const *, void const *));

int int_compare(void const *x, void const *y)
{
    int m, n;
    m = *((int *)x);
    n = *((int *)y);

    if (m == n)
        return 0;
    return m > n ? 1 : -1;
}
//qsort String

void qsortS(
    void *buf,
    size_t num,
    size_t size,
    int (*compare)(void const *, void const *));

int str_compare(void const *x, void const *y)
{
    char *m, *n;
    m = ((char*)x);
    n = ((char*)y);

    if (strcmp(m,n) == 0)
        return 0;
    return strcmp(m,n)>0 ? 1 : -1;
}

int main()
{
    int *a1, *a2;
    a1 = creatArray(SMALL_NUMBER);
    a2 = dumpArray(a1, SMALL_NUMBER);

    clock_t start, end;
    start = clock();
    sort(a1, 0, SMALL_NUMBER - 1);
    end = clock();
    printf("Sorting time is: %f seconds\n", (double)(end - start )/ CLOCKS_PER_SEC);

    start = clock();
    Quick_Sort(a1, 0, SMALL_NUMBER-1);
    end = clock();
    printf("Sorting time is: %f seconds\n", (double)(end - start )/ CLOCKS_PER_SEC);

    start = clock();
    qsort(a1, SMALL_NUMBER, sizeof(int), int_compare);
    end = clock();
    printf("Sorting time is: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(a1);
    free(a2);

    a1 = creatArray(HUGE_NUMBER);
    a2 = dumpArray(a1, HUGE_NUMBER);
    start = clock();
    sort(a1, 0, HUGE_NUMBER - 1);
    end = clock();
    printf("Sorting time is: %f seconds\n", (double)(end - start )/ CLOCKS_PER_SEC);
    start = clock();
    Quick_Sort(a1, 0, HUGE_NUMBER- 1);
    end = clock();
    printf("Sorting time is: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    qsort(a1, HUGE_NUMBER, sizeof(int), int_compare);
    end = clock();
    printf("Sorting time is: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    char s[][] = {"class", "C advance", "glass", "type", "mina"};
    strcpy(s, "abcdfklev");
    clock_t start, end;
    start = clock();
    qsortS(s, 5, sizeof(char*), str_compare);
    end = clock();
    printf("Sorting time is: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
