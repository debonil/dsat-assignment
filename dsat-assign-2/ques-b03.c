/*
Q. Implement the following sorting algorithms from scratch:
    3) Selection Sort Algorithm

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

void selectionSort(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        int minI = i;
        for (int j = i + 1; j < n; j++)
            if (arr[minI] > arr[j])
                minI = j;
        swap(&arr[minI], &arr[i]);
    }
}

int main()
{
    int n, *arr, k;
    scanf("%d", &n);
    arr = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    selectionSort(arr, n);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
