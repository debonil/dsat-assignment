// Q5. Create the Stack data structure from scratch using arrays. You will have to implement the Insert, Delete and Stack Trace operations.
// Submitted by Debonil Ghosh (M21AIE225)

#include <stdio.h>
#include <stdlib.h>

struct Stack
{
    int *array, top, maxSize;
};

struct Stack *createStack(int maxSize)
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->maxSize = maxSize;
    stack->top = -1;
    stack->array = (int *)malloc(stack->maxSize * sizeof(int));
    return stack;
}

void stackPush(struct Stack *stack, int val)
{
    if (stack->maxSize > (stack->top + 1))
    {
        stack->array[++stack->top] = val;
        printf("\t\t      [ %d ] pushed to stack! \n", val);
    }
    else
    {
        printf("\t\t\tError : Stack Over Flowed!! \n");
    }
}
int stackPop(struct Stack *stack)
{
    if (stack->top > -1)
    {
        int tmp = stack->array[stack->top--];
        printf("\t\t      [ %d ] poped from stack! \n", tmp);
        return tmp;
    }
    else
    {
        printf("\t\t      Error : Stack empty!! \n");
        return -1;
    }
}
void stackTrace(struct Stack *stack)
{
    printf("Stack trace : \n");
    if (stack->top > -1)
    {
        printf("\t\t\ttop -> %d \n", stack->array[stack->top]);
        int i = stack->top;
        while (--i > -1)
            printf("\t\t\t       %d \n", stack->array[i]);
    }
    else
    {
        printf("\t\t\tStack empty!! \n");
    }
}

int main()
{
    int n, option = -1, tmp;
    printf("Enter the max size of the Stack: \n");
    scanf("%d", &n);
    if (n < 1)
    {
        printf("Number of elements must be greater than zero! \n");
        return 0;
    }
    struct Stack *stack = createStack(n);
    while (option != 0)
    {
        printf("\nEnter \n 1. to Insert (push)\n 2. to Delete (pop)\n 3. to See stack trace\n 0. to Exit\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            printf("Enter value to insert:\n");
            scanf("%d", &tmp);
            stackPush(stack, tmp);
            break;
        case 2:
            stackPop(stack);
            break;
        case 3:
            stackTrace(stack);
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
