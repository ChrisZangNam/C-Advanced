#include <stdio.h>
#include <stdlib.h>
#include "jval.h"

void *memcpy(void *region1, const void *region2, size_t n)
{
    const char *first = (const char *)region2;
    const char *last = ((const char *)region2) + n;
    char *result = (char *)region1;
    while (first != last)
        *result++ = *first++;
    return result;
}

void exch(void *buf, int size, int i, int j)
{
    void *temp = malloc(size);
    memcpy(temp, (char *)buf + i * size, size);
    memcpy((char *)buf + i * size, (char *)buf + j * size, size);
    memcpy((char *)buf + j * size, temp, size);

    free(temp);
}

void sort_gen(Jval a[], int l, int r, int (*compare)(Jval*, Jval*))
{
    if (r <= l)
        return;
    int i = l - 1, j = r;
    int p = l - 1, q = r;

    while (1)
    {
        while (compare(&a[++i], &a[r]) < 0)
            ;
        while (compare(&a[r], &a[--j]) < 0)
            if (j == l)
                break;
        if (i >= j)
            break;
        exch(a, sizeof(Jval), i, j);
        if (compare(&a[i], &a[r]) == 0)
            exch(a, sizeof(Jval), ++p, i);
        if (compare(&a[j], &a[r]) == 0)
            exch(a, sizeof(Jval), --q, j);
    }
    exch(a,sizeof(Jval), i, r);
    j = i - 1;
    i = i + 1;
    for (int k = l; k <= p; k++)
        exch(a,sizeof(Jval), k, j--);
    for (int k = r - 1; k >= q; k--)
        exch(a,sizeof(Jval), k, i++);
    sort_gen(a, l, j, compare);
    sort_gen(a, i, r, compare);
}

int compare_i(Jval* a, Jval* b)
{
    return a->i == b->i ? 0 : a->i > b->i ? 1 : -1;
}

int compare_int(Jval *a, int x)
{
    return a->i == x ? 0 : a->i > x ? 1 : -1;
}

int search(Jval a[] , int l, int r, int x)

{
    int i, res;
    if (r < l)
        return -1;
    i = (l + r) / 2;
    res = compare_int(&a[i], x);
    if (res == 0)
        return i;
    else if (res < 0)
        return search(a, l, i - 1, x);
    else
        return search(a, i + 1, r, x);
}

Jval *create_array_i(int size)
{
    Jval *a = malloc(sizeof(Jval) * size);

    for (int i = 0; i < size; i++)
    {
        a[i].i = rand() % 100;
    }

    return a;
}

void outputJval_i(Jval arr[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%5d", arr[i].i);
    printf("\n");
}

int main()
{
    Jval *a;

    a = create_array_i(10);
    sort_gen(a, 0, 9, compare_i);
    outputJval_i(a, 10);

}
