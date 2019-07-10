#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int check(int *a, int n, int m)
{
    int count = 0;
    for (int i = 0; i < n; i++)
        if(a[i] == 1)
            count++;
    if(count == m)
        return 1;
    return 0;
}

void solution(int *a, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d", a[i]);

    printf("\n");
}

void TRY(int k, int *a, int n, int m)
{

    for (int val = 0; val < 2; val++)
    {
        a[k] = val;

        if(k == (n-1))
        {
            int count = 0;
            for (int i = 0; i < n; i++)
                if(a[i] == 1)
                    count++;
            if(count == m)
                solution(a, n);
        }
        else TRY(k+1, a, n, m);
    }
}

int chiadia(int n)
{
    srand(time(NULL));
    int r, s;
    if(n == 1)
        return 0;
    else
    {
        r = rand() % (n - 1) + 1;
        s = n - r;
    }
    return (s + r) * r * s + chiadia(r) + chiadia(s);
}

double S1(int n)
{
    srand(time(NULL));
    int r, s;
    if (n == 1)
        return 0;
    else
    {
        r = rand() % (n - 1) + 1;
        s = n - r;
    }
    return ((double)1/r + (double)1/s) + S1(r) + S1(s);
}


/*void TRY(int *a, int n, int m, int k, int i)
{
    for (i; i < n - m + k + 1; i++)
    {
        a[k] = i+1;
        if(k == m-1)
            solution(a,k+1);
        else
            TRY(a, n, m, k + 1, i + 1);
    }
}*/

int main()
{
    int n, m;
    printf("Nhap n= ");
    scanf("%d", &n);
  /*  printf("Nhap m= ");
    scanf("%d", &m);

    int a[n];

    TRY(a,n,m,0,0);*/

    printf("S(%d) = %lf\n", n, S1(n));
}
