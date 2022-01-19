/*
Q. Implement the following search algorithms from scratch:
     1) Linear Search Algorithm

 Submitted by Debonil Ghosh (M21AIE225)
*/

#include <stdio.h>
#include <stdlib.h>

int linearSearch(int n, int *arr, int k)
{
    for (int i = 0; i < n; i++)
        if (arr[i] == k)
            return 1; // i;
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
    printf("%d\n", linearSearch(n, arr, k));
    return 0;
}
