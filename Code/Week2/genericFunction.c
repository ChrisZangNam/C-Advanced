#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* creatArray(int size)
{
    int *a = malloc(sizeof(int)*size);

    //srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        a[i] = rand() % 11;
    }

    return a;
}

int search(
    void *buf, int size,
    int l, int r,
    void *item,
    int (*compare)(void *, void *))
{
    int i, res;
    if (r < l)
        return -1;
    i = (l + r) / 2;
    res = compare(item, (char *)buf + (size * i));
    if (res == 0)
        return i;
    else if (res < 0)
        return search(buf, size, l, i - 1, item, compare);
    else
        return search(buf, size, i + 1, r, item, compare);
}

int int_compare(void const *x, void const *y)
{
    int m, n;
    m = *((int *)x);
    n = *((int *)y);
    if (m == n)
        return 0;
    return m > n ? 1 : -1;
}

void qsort(
    void *buf,
    size_t num,
    size_t size,
    int (*compare)(void const *, void const *));

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

void q3sort(void *a, int size, int l, int r, int (*compare)(void const *, void const *))
{
    if(r<=l)
        return;
    int i = l - 1, j = r;
    int p = l - 1, q = r;

    while(1)
    {
        while(compare((char *)a + (++i)*size, (char*)a + r*size) < 0)
            ;
        while(compare((char*)a + r*size, (char*)a + (--j)*size) < 0)
            if(j==l)
                break;
        if(i>=j)
            break;
        exch(a, size, i, j);
        if(compare((char*)a + i*size, (char*)a + r*size) == 0)
            exch(a, size, ++p, i);
        if (compare((char *)a + j * size, (char *)a + r * size) == 0)
            exch(a, size, --q, j);
    }
    exch(a, size, i, r);
    j = i - 1;
    i = i + 1;
    for (int k = l; k <= p; k++)
        exch(a, size, k, j--);
    for (int k = r - 1; k >= q; k--)
        exch(a, size, k, i++);
    q3sort(a, size, l, j, compare);
    q3sort(a, size, i, r, compare);
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%5d", arr[i]);
    printf("\n");
}

int main()
{
    int size = 10;
    int *arr;
    int item;

    /*printf("Enter size of array is: ");
    scanf("%d", &size);*/

    arr = creatArray(size);
  //  qsort(arr, size, sizeof(int), int_compare);
    printArray(arr, size);
    q3sort(arr, sizeof(int), 0, 9, int_compare);

    //exch(arr, sizeof(int), 1, 5);

    printArray(arr, size);
    /*printf("Enter item = ");
    scanf("%d", &item);

    int res = search(arr, sizeof(int), 0, 9, &item, int_compare);

    printf("%d\n", res);*/

    return 0;
}
