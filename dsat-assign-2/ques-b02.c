/*
Q. Implement the following sorting algorithms from scratch:
    2) Insertion Sort Algorithm

 Submitted by Debonil Ghosh (M21AIE225)
*/

#include <stdio.h>
#include <stdlib.h>

void insertionSort(int *arr, int n)
{
    for (int i = 1; i < n; i++)
    {
        int k = arr[i], j = i - 1;
        while (j > -1 && arr[j] > k)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = k;
    }
}

int main()
{
    int n, *arr, k;
    scanf("%d", &n);
    arr = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    insertionSort(arr, n);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
