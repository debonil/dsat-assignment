// Q4. Given an array of size n, print the difference between the largest and smallest element present in the array.
// Submitted by Debonil Ghosh (M21AIE225)

#include <stdio.h>

int main()
{
    int n, tmp, min = 2147483647, max = -2147483648;
    printf("Enter the size of the array: \n");
    scanf("%d", &n);
    if (n < 1)
    {
        printf("Number of elements must be greater than zero! \n");
        return 0;
    }
    printf("Enter array elements ...\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &tmp);
        if (tmp < min)
            min = tmp;
        if (tmp > max)
            max = tmp;
    }

    printf("Difference between the largest and smallest element is : %d \n", (max - min));

    return 0;
}
