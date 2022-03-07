/* 3) Given a sorted array of n distinct integers where each integer is in the range
from s to e and e>s. Using Order Statistics, find the smallest number that is
missing from the array.

    Input:
    n = 6, s=17 , e =36
    12, 13 , 14, 17, 25, 36

    Output:
    18

=============================================================
6 17 36
12 13 14 17 25 36
*/
// Submitted by Debonil Ghosh (M21AIE225)

#include <stdio.h>
#include <stdlib.h>

int anyGapByOrderStats(int *arr, int si, int ei)
{
    int indexGap = ei - si;
    int valueGap = arr[ei] - arr[si];
    return valueGap > indexGap;
}

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

int binarySearchGap(int *arr, int si, int ei)
{
    int hi = ei, lo = si, mid, missedNumber = arr[si];
    while ((lo + 1) < hi)
    {
        mid = (lo + hi) / 2;
        if (anyGapByOrderStats(arr, lo, mid))
            hi = mid - 1;
        else
        {
            lo = mid + 1;
            missedNumber = arr[mid];
        }
    }
    return missedNumber + 1;
}

int main()
{
    int n, s, e, *arr, si, ei;
    scanf("%d", &n);
    scanf("%d", &s);
    scanf("%d", &e);
    arr = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    // log n
    si = binarySearch(n, arr, s);
    // log n
    ei = binarySearch(n, arr, e);

    // log n
    printf("%d\n", binarySearchGap(arr, si, ei));
    return 0;
}
