/*
Q. 1) There are n rectangular bars with some lengths. The task is to modify the lengths
such that each rectangular bar has the same length. You can lengthen or shorten
each rectangular bar. Both operations cost z where z is the difference between
the new and original length. Find the minimum total cost?

 Submitted by Debonil Ghosh (M21AIE225)
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, *arr, sum = 0, avg = 0;
    scanf("%d", &n);
    arr = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }
    avg = sum / n;
    sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i] > avg ? arr[i] - avg : avg - arr[i];
    }
    printf("%d \n", sum);
    return 0;
}
