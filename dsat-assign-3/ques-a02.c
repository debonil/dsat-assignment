/*
Q. Implement the following sorting algorithms from scratch:
     2) Counting Sort Algorithm

 Submitted by Debonil Ghosh (M21AIE225)
*/

#include <stdio.h>
#include <stdlib.h>
#define RANGE 1000

void countingSort(int *arr, int n)
{

    int ref[RANGE] = {0}, *tmp = (int *)calloc(n, sizeof(int)), min = arr[0];

    // handling negative values
    for (int i = 1; i < n; i++)
        if (arr[i] < min)
            min = arr[i];
    if (min < 0)
        for (int i = 0; i < n; i++)
            arr[i] = arr[i] - min;

    // sorting started
    for (int i = 0; i < n; i++)
        ref[arr[i]]++;
    for (int i = 1; i < RANGE; i++)
        ref[i] += ref[i - 1];
    for (int i = n - 1; i > -1; i--)
        tmp[--ref[arr[i]]] = arr[i];
    for (int i = 0; i < n; i++)
        arr[i] = tmp[i];

    // handling negative values
    if (min < 0)
        for (int i = 0; i < n; i++)
            arr[i] = arr[i] + min;
}

int main()
{
    int n, *arr, k;
    scanf("%d", &n);
    arr = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    countingSort(arr, n);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
