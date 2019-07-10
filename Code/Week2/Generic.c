#include <stdio.h>
#include <stdlib.h>


void* memcpy(void* region1, const void* region2, size_t n)
{
    const char *first = (const char *)region2;
    const char *last = ((const char *)region2) + n;
    char *result = (char *)region1;
    while(first != last)
        *result++ = *fisrt++;
    return result;
}

int search(
    void *buf,int size,
    int l, int r,
    void *item,
    int (*compare)(void *, void *))
{
    int i, res;
    if(r<l)
        return -1;
    i = (l + r) / 2;
    res = compare(item, (char *)buf + (size * i));    if(res == 0)
        return i;
    else if(res < 0)
        return search(buf, size, l, i - 1, item, compare);
    else
        return search(buf, size, i + 1, r, item, compare);
}

void qsort(
    void *buf,
    size_t num,
    size_t size,
    int (*compare)(void const *, void const *));

int int_compare(void const* x, void const *y){
    int m, n;
    m = *((int *)x);
    n = *((int *)y);
    if(m == n)
        return 0;
    return m > n ? 1 : -1;
}

void swap(void* a, void* b, size_t size)
{
    void *temp = malloc(size);
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
}

void exch(void *buf, int size, int i, int j)
{
    void *temp = malloc(size);
    memcpy(temp, (char *)buf + i * size, size);
    memcpy((char *)buf + i * size, (char *)buf + j * size, size);
    memcpy((char *)buf + j * size, temp, size);
}

int main()
{
    int a[100], i, res;
    int n = 100, item = 5;
    for (i = 0; i < n; i++)
        a[i] = rand();
    qsort(a, n, sizeof(int), int_compare);
    res = search(a, sizeof(int), 0, n - 1, &item, int_compare);
}
