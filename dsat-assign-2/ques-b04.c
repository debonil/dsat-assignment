/*
Q. Implement the following sorting algorithms from scratch:
    4) Radix Sort Algorithm

 Submitted by Debonil Ghosh (M21AIE225)
*/

#include <stdio.h>
#include <stdlib.h>

void countingSort(int *arr, int n, int plc)
{
    int ref[10] = {0}, tmp[n] = {0};
    for (int i = 0; i < n; i++)
        ref[(arr[i] / plc) % 10]++;
    for (int i = 1; i < 10; i++)
        ref[i] += ref[i - 1];
    for (int i = n - 1; i > -1; i--)
        tmp[--ref[(arr[i] / plc) % 10]] = arr[i];
    for (int i = 0; i < n; i++)
        arr[i] = tmp[i];
}
void radixSort(int *arr, int n)
{
    int max = arr[0], min = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
        if (arr[i] < min)
            min = arr[i];
    }
    if (min < 0)
    {
        max -= min;
        for (int i = 0; i < n; i++)
            arr[i] -= min;
    }
    for (int p = 1; max / p > 0; p *= 10)
        countingSort(arr, n, p);

    if (min < 0)
        for (int i = 0; i < n; i++)
            arr[i] += min;
}

int main()
{
    int n, *arr, k;
    scanf("%d", &n);
    arr = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    radixSort(arr, n);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
