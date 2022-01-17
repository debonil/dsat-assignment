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
            return mid;
        else if (arr[mid] < k)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    return -1;
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
    // assuming entered array is sorted
    printf("%d\n", binarySearch(n, arr, k));
    return 0;
}
