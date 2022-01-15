// Q11. Create the min-heap data structure, implementing create heap, insert element and delete min operations.
// Submitted by Debonil Ghosh (M21AIE225)

#include <stdio.h>
#include <stdlib.h>

struct Heap
{
    int *refArr;
    int size;
};

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
int lChild(int i) { return i * 2; }
int rChild(int i) { return i * 2 + 1; }

void heapifyUp(struct Heap *heap, int i)
{
    if (heap->refArr[parent(i)] > heap->refArr[i])
    {
        swap(&heap->refArr[parent(i)], &heap->refArr[i]);
        heapifyUp(heap, parent(i));
    }
}

void heapifyDown(struct Heap *heap, int i)
{
    if (heap->refArr[parent(i)] > heap->refArr[i])
    {
        swap(&heap->refArr[parent(i)], &heap->refArr[i]);
        heapifyUp(heap, parent(i));
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
    int option = -1, tmp;
    struct Heap *heap = createHeap(25);
    while (option != 0)
    {
        printf("\nEnter \n 1. to Insert \n 2. to Delete Min \n 3. to See All\n 0. to Exit\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            printf("Enter value to insert:\n");
            scanf("%d", &tmp);
            addToHeap(heap, tmp);
            show(heap);
            break;
        case 2:
            heapRemoveMin(heap);
            show(heap);
            break;
        case 3:
            show(heap);
            break;
        case 0:
            printf("\n");
            break;

        default:
            printf("Enter valid option..\n");
            break;
        }
    }

    return 0;
}
