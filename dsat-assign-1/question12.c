// Q12. Given an array of 'n' elements, find the ‘k’th largest element. Use the max-heap data structure to help solve your purpose.
// Submitted by Debonil Ghosh (M21AIE225)

#include <stdio.h>
#include <stdlib.h>

struct Heap
{
    int *refArr;
    int size;
};
int heapComp(int a, int b)
{
    return a < b;
}
struct Heap *createHeap(int maxSize)
{
    struct Heap *heap = (struct Heap *)malloc(sizeof(struct Heap));
    heap->refArr = (int *)calloc(maxSize, sizeof(int));
    heap->size = 0;
    return heap;
}
void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}
int parent(int i) { return (i - 1) / 2; }
int lChild(int i) { return i * 2 + 1; }
int rChild(int i) { return i * 2 + 2; }

void heapifyUp(struct Heap *heap, int i)
{
    if (heapComp(heap->refArr[parent(i)], heap->refArr[i]))
    {
        swap(&heap->refArr[parent(i)], &heap->refArr[i]);
        heapifyUp(heap, parent(i));
    }
}

void heapifyDown(struct Heap *heap, int i)
{
    int l = lChild(i);
    int r = rChild(i);
    int best = i;

    if (l < heap->size && l > -1 && !heapComp(heap->refArr[l], heap->refArr[best]))
    {
        best = l;
    }
    if (r < heap->size && r > -1 && !heapComp(heap->refArr[r], heap->refArr[best]))
    {
        best = r;
    }
    if (best != i)
    {
        swap(&heap->refArr[best], &heap->refArr[i]);
        heapifyDown(heap, best);
    }
}

void addToHeap(struct Heap *heap, int val)
{
    heap->refArr[heap->size] = val;
    heapifyUp(heap, heap->size++);
}

int smallest(struct Heap *heap)
{
    return heap->refArr[0];
}
int heapRemoveMin(struct Heap *heap)
{
    int min = heap->refArr[0];
    heap->refArr[0] = heap->refArr[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return min;
}
void show(struct Heap *heap)
{
    if (heap != NULL)
    {
        for (int i = 0; i < heap->size; i++)
        {
            printf("\t[ %d ] ", heap->refArr[i]);
            if (i == 0 || i == 2 || i == 6 || i == 14)
                printf("\n");
        }
    }
}

int main()
{
    int n, k;
    printf("\nEnter number of elements of the array:\n");
    scanf("%d", &n);
    struct Heap *heap = createHeap(n);
    printf("\nEnter all [ %d ] elements of the array separated by space:\n", n);
    for (int i = 0; i < n; i++)
    {
        int t;
        scanf("%d", &t);
        addToHeap(heap, t);
    }
    printf("\nMax Heap formed :\n");
    show(heap);
    printf("\nEnter the value of k  to find the ‘k’th largest element:\n");
    scanf("%d", &k);
    for (int i = 0; i < k - 1; i++)
    {
        printf("\nMax Heap formed after heapRemoveMin %d:\n", i);
        heapRemoveMin(heap);
        show(heap);
    }
    printf("\nThe ‘k’th largest element is [ %d ]\n\n", smallest(heap));
    return 0;
}
