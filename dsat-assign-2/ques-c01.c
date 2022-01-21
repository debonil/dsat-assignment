/*
Q. 1) There are n rectangular bars with some lengths. The task is to modify the lengths
such that each rectangular bar has the same length. You can lengthen or shorten
each rectangular bar. Both operations cost z where z is the difference between
the new and original length. Find the minimum total cost?

 Submitted by Debonil Ghosh (M21AIE225)
*/

#include <stdio.h>
#include <stdlib.h>

void sort(int *arr, int n)
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
    int n, *arr, sum = 0, med = 0;
    scanf("%d", &n);
    arr = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    sort(arr, n);
    med = n % 2 ? arr[n / 2] : (arr[n / 2] + arr[n / 2 - 1]) / 2;
    for (int i = 0; i < n; i++)
        sum += arr[i] > med ? arr[i] - med : med - arr[i];
    printf("%d \n", sum);
    return 0;
}
