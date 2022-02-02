
// DSAT Assignment 1
// Q11. Create the min-heap data structure, implementing create heap, insert element and delete min operations.
// Submitted by Debonil Ghosh (M21AIE225)

#include <stdio.h>
#include <stdlib.h>

struct Heap
{
    char *refArr;
    int size;
};
// need to be implented later
int heapComp(char a, char b);
/* {
    return a > b;
} */
struct Heap *createHeap(int maxSize)
{
    struct Heap *heap = (struct Heap *)malloc(sizeof(struct Heap));
    heap->refArr = (char *)calloc(maxSize, sizeof(char));
    heap->size = 0;
    return heap;
}
void swap(char *a, char *b)
{
    char c = *a;
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

void addToHeap(struct Heap *heap, char val)
{
    heap->refArr[heap->size] = val;
    heapifyUp(heap, heap->size++);
    for (int i = 0; i < heap->size; i++)
        printf("\t[ %c ] ", heap->refArr[i]);
    printf("\n");
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
            printf("\t[ %c ] ", heap->refArr[i]);
            if (i == 0 || i == 2 || i == 6 || i == 14)
                printf("\n");
        }
    }
}

int testmain()
{
    int option = -1, tmp;
    struct Heap *heap = createHeap(25);
    // for test
    addToHeap(heap, 50);
    addToHeap(heap, 60);
    addToHeap(heap, 40);
    addToHeap(heap, 70);
    addToHeap(heap, 80);
    addToHeap(heap, 90);
    addToHeap(heap, 30);
    addToHeap(heap, 45);
    addToHeap(heap, 65);
    addToHeap(heap, 75);
    addToHeap(heap, 95);
    addToHeap(heap, 35);
    ;
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
