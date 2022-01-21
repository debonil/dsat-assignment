// Q7. Check if an arithmetic expression has balanced parenthesis or not using the stack data structure.
// Submitted by Debonil Ghosh (M21AIE225)

#include <stdio.h>
#include <stdlib.h>

struct Stack
{
    char *array, top, maxSize;
};

struct Stack *createStack(int maxSize)
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->maxSize = maxSize;
    stack->top = -1;
    stack->array = (char *)malloc(stack->maxSize * sizeof(char));
    return stack;
}

void stackPush(struct Stack *stack, char val)
{
    if (stack->maxSize > (stack->top + 1))
    {
        stack->array[++stack->top] = val;
        printf("\t\t      [ %c ] pushed to stack! \n", val);
    }
    else
    {
        printf("\t\t\tError : Stack Over Flowed!! \n");
    }
}
int isEmpty(struct Stack *stack)
{
    if (stack->top < 0)
        return 1;
    else
        return 0;
}
int stackPop(struct Stack *stack)
{
    if (!isEmpty(stack))
    {
        int tmp = stack->array[stack->top--];
        printf("\t\t      [ %c ] poped from stack! \n", tmp);
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
    if (!isEmpty(stack))
    {
        printf("\t\t\ttop -> %c \n", stack->array[stack->top]);
        int i = stack->top;
        while (--i > -1)
            printf("\t\t\t       %c \n", stack->array[i]);
    }
    else
    {
        printf("\t\t\tStack empty!! \n");
    }
}

int main()
{
    char exp[25], *s;
    printf("Enter arithmatic expression to check: \n");
    scanf("%s", &exp);
    s = exp;
    struct Stack *stack = createStack(25);
    while (*s != '\0')
    {
        if (*s == '(')
            stackPush(stack, *s);
        else if (*s == ')')
        {
            if (isEmpty(stack))
                break;
            else
                stackPop(stack);
        }
        s++;
    }
    if (isEmpty(stack) && *s == '\0')
    {
        printf("\nArithmatic expression BALANCED! \n\n");
    }
    else
    {
        printf("\nArithmatic expression NOT BALANCED! \n\n");
    }

    return 0;
}
