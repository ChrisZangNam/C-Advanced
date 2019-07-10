#include <stdio.h>

#define Max_Size 10

typedef int DataType;

//MERGE SORT
void Merge(DataType a[], int first, int mid, int last)
{
   DataType tmp[Max_Size];
   int first1 = first; int last1 = mid; //day con 1
   int first2 = mid + 1; int last2 = last; //day con 2
   int index = first1;

   //tron 2 day con voi nhau
   for( ; first1 <= last1 && first2 <= last2; ++index)
   {
      if(a[first1] < a[first2])
      {
         tmp[index] = a[first1];
         ++first1;
      }
      else{
         tmp[index] = a[first2];
         ++first2;
      }
   }

   //trong trh 2 day co so phan tu khac nhau
   for( ; first1 <= last1; ++first1, ++index)
      tmp[index] = a[first1];
   for( ; first2 <= last2; ++first2, ++index)
      tmp[index] = a[first2];

   //sao tra lai mang ban dau
   for(index = first; index <= last; ++index)
      a[index] = tmp[index];
}

void Merge_Sort(DataType a[], int first, int last)
{
   if(first < last){
      //chia thanh 2 day con
      int mid = (first + last)/2;
      //Sap xep day con trai tu first-mid
      Merge_Sort(a, first, mid);
      //sap xep day con phai tu mid+1-last
      Merge_Sort(a, mid+1, last);
      //tron 2 day con
      Merge(a, first, mid, last);
   }
}

//QUICK SORT 2 way
void swap(DataType *a, DataType *b)
{
   DataType tmp = *a;
   *a = *b;
   *b = tmp;
}

int Partition(DataType a[], int L, int R, int indexPivot)
{
   int pivot = a[indexPivot];
   swap(&a[indexPivot], &a[R]);

   int storeIndex = L;

   for(int i=L; i<R; i++)
   {
      if(a[i] < pivot){
         swap(&a[i], &a[storeIndex]);
         storeIndex++;
      }
   }

   swap(&a[storeIndex], &a[R]); //dua pivot ve vtri storeIndex

   return storeIndex;
}

void Quick_Sort(DataType a[], int L, int R)
{
   if(L<R)
   {
      int index = (L+R)/2;
      index = Partition(a, L, R, index);

      if(L < index)
         Quick_Sort(a, L, index-1);
      if(index < R)
         Quick_Sort(a, index+1, R);
   }
}

void exch(int a[], long i, long j)
{
   int tmp = a[i];
   a[i] = a[j];
   a[j] = tmp;
}
//Quick_3way
void QuickSort_3way(int a[], int L, int R)
{
   if (R <= L)
      return;

   int i = L - 1, j = R;
   int p = L - 1, q = R;

   while (1)
   {
      while (a[++i] < a[R])
         ;
      while (a[R] < a[--j])
         if (j == L)
            break;
      if (i >= j)
         break;
      exch(a, i, j);
      if (a[i] == a[R])
         exch(a, ++p, i);
      if (a[j] == a[R])
         exch(a, --q, j);
   }
   exch(a, i, R);
   j = i - 1;
   i = i + 1;
   for (int k = L; k <= p; k++)
      exch(a, k, j--);
   for (int k = R - 1; k >= q; k--)
      exch(a, k, i++);
   QuickSort_3way(a, L, j);
   QuickSort_3way(a, i, R);
}

//HEAP SORT

//vun lai dong tu nut thu i
void heapify(DataType a[], int i, int n) //n=heapsize[a], nut thu i
{
   int L = 2*i; //left node
   int R = 2*i +1; //right node
   int max = i;

   if(L <= n && a[L] > a[i])
      max = L;
   if(R <= n && a[R] > a[max])
      max = R;
   if(max != i){
      swap(&a[i], &a[max]);
      heapify(a, max, n);
   }
}

void buildHeap(int a[], int n)
{ //array is a [1.2.3...n]

   for(int i = n/2; i >= 1; i--)
   {
      heapify(a, i, n);
   }
}

void Heap_Sort(int a[], int n)
{
   buildHeap(a, n);

   for(int i = n; i > 1; i--)
   {
      swap(&a[1], &a[i]);
      heapify(a, 1, i-1);
   }
}

//Insertion Sort
void insertionSort(DataType a[], int n){
   int i, j;
   DataType next;

   for(i=1; i<n; i++)
   {
      next = a[i];
      for(j=i-1; j>=0 && next < a[j]; j--)
         a[j+1] = a[j];

      a[j+1] = next;
   }
}

//Selection Sort
void SelectionSort(DataType a[], int n)
{
   int i,j, min, tmp;
   for(i=0; i<n-1; i++)
   {
      min = i;
      for(j=i+1; j<=n-1; j++)
      {
         if(a[j] < a[min])
            min =j;
      }
      tmp = a[i];
      a[i] = a[min];
      a[min] = tmp;
   }
}
