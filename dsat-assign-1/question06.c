// Q6. Create the Queue from scratch using structures and pointers. You will have to implement the Insert, Delete and ‘Display All Elements’ operations.
// Submitted by Debonil Ghosh (M21AIE225)

#include <stdio.h>
#include <stdlib.h>

struct Queue
{
    struct QueueNode *rear, *front;
};
struct QueueNode
{
    int val;
    struct QueueNode *next;
};

struct Queue *createQueue()
{
    struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
    queue->rear = NULL;
    queue->front = NULL;
    return queue;
}

void queueAdd(struct Queue *queue, int val)
{
    struct QueueNode *newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    newNode->val = val;
    if (queue->rear != NULL)
        queue->rear->next = newNode;
    else
        queue->front = newNode;

    queue->rear = newNode;
    printf("\t\t      [ %d ] added to the Queue! \n", val);
}
int queueRemove(struct Queue *queue)
{
    if (queue->front != NULL)
    {
        struct QueueNode *tmpNode = queue->front;
        int tmp = tmpNode->val;
        queue->front = tmpNode->next;
        free(tmpNode);
        if (queue->front == NULL)
            queue->rear = NULL;
        printf("\t\t      [ %d ] removed from Queue! \n", tmp);
        return tmp;
    }
    else
    {
        printf("\t\t      Error : Queue empty!! \n");
        return -1;
    }
}
void queueTrace(struct Queue *queue)
{
    printf("queue trace : \n");
    if (queue->front != NULL)
    {
        printf("\t\t\tfront ->");
        struct QueueNode *n = queue->front;
        while (n != NULL)
        {
            printf("\t[ %d ]", n->val);
            n = n->next;
        }

        printf("\t <-rear \n");
    }
    else
    {
        printf("\t\t\tQueue empty!! \n");
    }
}

int main()
{
    int option = -1, tmp;
    struct Queue *queue = createQueue();
    while (option != 0)
    {
        printf("\nEnter \n 1. to Insert (enqueue)\n 2. to Delete (dequeue)\n 3. to See all elements\n 0. to Exit\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            printf("Enter value to insert:\n");
            scanf("%d", &tmp);
            queueAdd(queue, tmp);
            break;
        case 2:
            queueRemove(queue);
            break;
        case 3:
            queueTrace(queue);
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
