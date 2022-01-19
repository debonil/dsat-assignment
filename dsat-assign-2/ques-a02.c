/*
Q. Implement the following search algorithms from scratch:
     2) Binary Search Algorithm

 Submitted by Debonil Ghosh (M21AIE225)
*/

#include <stdio.h>
#include <stdlib.h>

int binarySearch(int n, int *arr, int k)
{
    int hi = n, lo = 0, mid;
    while (lo <= hi)
    {
        mid = (lo + hi) / 2;
        if (arr[mid] == k)
            return 1; // mid;
        else if (arr[mid] < k)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    return -1;
}
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
    {
        scanf("%d", &arr[i]);
    }
    scanf("%d", &k);
    insertionSort(arr, n);
    printf("%d\n", binarySearch(n, arr, k));
    return 0;
}
