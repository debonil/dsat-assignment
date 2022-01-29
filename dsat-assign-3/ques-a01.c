/*
Q. Implement the following sorting algorithms from scratch:
     1) Heap Sort Algorithm

 Submitted by Debonil Ghosh (M21AIE225)
*/

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

void heapify(int *arr, int n, int currNode)
{
    int largest = currNode;
    int leftChild = 2 * currNode + 1;
    int rightChild = 2 * currNode + 2;

    if (leftChild < n && arr[leftChild] > arr[largest])
        largest = leftChild;

    if (rightChild < n && arr[rightChild] > arr[largest])
        largest = rightChild;

    if (largest != currNode)
    {
        swap(&arr[currNode], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int *arr, int n)
{
    // O(n)
    for (int i = n / 2 - 1; i > -1; i--)
        heapify(arr, n, i);

    // O(nlogn)
    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        // O(logn)
        heapify(arr, i, 0);
    }
}

int main()
{
    int n, *arr, k;
    scanf("%d", &n);
    arr = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    heapSort(arr, n);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
