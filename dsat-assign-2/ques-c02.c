/*
Q. Given an integer array containing n elements with possibly duplicate elements,
    the task is to find indexes of the first and last occurrences of an element x in the
    given array.

 Submitted by Debonil Ghosh (M21AIE225)
*/

#include <stdio.h>
#include <stdlib.h>

int *linearSearch(int n, int *arr, int k)
{
    int *r = (int *)calloc(n, sizeof(int));
    r[0] = r[1] = -1;
    for (int i = 0; i < n; i++)
        if (arr[i] == k)
            if (r[0] < 0)
                r[0] = r[1] = i;
            else
                r[1] = i;
    return r;
}

int main()
{
    int n, *arr, k;
    scanf("%d", &n);
    arr = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    scanf("%d", &k);
    int *r = linearSearch(n, arr, k);
    printf("%d %d\n", r[0], r[1]);
    return 0;
}
