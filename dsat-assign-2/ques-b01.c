/*
Q. Implement the following sorting algorithms from scratch:
    1) Quick Sort Algorithm

 Submitted by Debonil Ghosh (M21AIE225)
*/

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}
void printArr(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int partition(int arr[], int start, int end)
{
    int pivot = arr[start], i = start + 1, j = start + 1;
    for (; i <= end; i++)
        if (arr[i] < pivot)
            swap(&arr[i], &arr[j++]);
    swap(&arr[start], &arr[j-1]);
    return j-1;
}
void quickSortImpl(int *arr, int start, int end)
{
    if (start < end)
    {
        int pivot = partition(arr, start, end);
        quickSortImpl(arr, start, pivot - 1);
        quickSortImpl(arr, pivot + 1, end);
    }
}
void quickSort(int *arr, int n)
{
    quickSortImpl(arr, 0, n - 1);
}

int main()
{
    int n, *arr, k;
    scanf("%d", &n);
    arr = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    quickSort(arr, n);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
