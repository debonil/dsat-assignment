/*
Q1. Given a formula in propositional logic, write a code to put appropriate and
    necessary brackets in the formula following the precedence order of operators.
    If not possible, output “Not well formed formula”.

Note-1: We will use the following characters for different operators:
AND: &
OR : |
NOT : !
IMPLICATION : >
BICONDITIONAL : ~


Note-2: Each propositional symbol will be denoted by a capital letter (e.g., A, B, C, …, etc.).

Note-3: The input formula will never contain the truth values “True” and “False”.

*/
// Submitted by Debonil Ghosh (M21AIE225)

#include <stdio.h>
#include <string.h>
// importing DSAT Assignment 1 Q no 11
#include "heap.h"

static const char OPS_PRECDNCE[] = "~>&|!";
static const char BI_DIR_OPS[] = "~&|";
static const char UNI_DIR_OPS[] = ">";
static const char UNIARY_OPS[] = "!";

static char PAREN_OPEN[] = "(";
static char PAREN_CLOSE[] = ")";

static const char NOT_WFF[] = "Not well formed formula";

int indexOf(const char *str, char c)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == c)
            return i;
        i++;
    }
    return -1;
}
int isOperator(char c)
{
    return indexOf(OPS_PRECDNCE, c) > -1 ? 1 : 0;
}
int isUnary(char c)
{
    return UNIARY_OPS[0] == c; // indexOf(UNIARY_OPS, c) > -1 ? 1 : 0;
}
int isUniDirOps(char c)
{
    return UNI_DIR_OPS[0] == c; // indexOf(UNIARY_OPS, c) > -1 ? 1 : 0;
}
int getPrec(char c)
{
    return indexOf(OPS_PRECDNCE, c);
}
/* int strlen(const char *s)
{
    int i = 0;
    while (*(s + i) != '\0')
        i++;
    return i;
} */
/* const char * strcat(const char *s1,const char *s2)
{
    int l1 = strlen(s1), l2 = strlen(s2);
    const char * buf = (char *)calloc((l1+l2), sizeof(char));
    int i = 0;
    while (*s1!= '\0')
        i++;
    return i;
} */
int heapComp(char a, char b)
{
    int opa = isOperator(a);
    int opb = isOperator(b);
    if (opa != opb)
        return opa < opb;
    if (opa)
    {
        int preca = getPrec(a);
        int precb = getPrec(b);
        return preca > precb;
    }
    return 0;
}
const char *getParenthesisStr(struct Heap *heap, int i)
{
    char *buff = (char *)calloc((heap->size * 3), sizeof(char));
    if (i < heap->size && i > -1)
    {
        char op = heap->refArr[i];
        if (isOperator(op))
        {
            strcat(buff, PAREN_OPEN);
            strcat(buff, getParenthesisStr(heap, lChild(i)));
            strncat(buff, &op, 1);
            strcat(buff, getParenthesisStr(heap, rChild(i)));
            strcat(buff, PAREN_CLOSE);
        }
        else
        {
            strncat(buff, &op, 1);
        }
    }

    return buff;
}
const char *addParenthesis(struct Heap *heap)
{
    if (heap != NULL && heap->size > 0)
    {
        char *buff = (char *)calloc((heap->size * 3), sizeof(char));
        strcat(buff, getParenthesisStr(heap, lChild(0)));
        strncat(buff, heap->refArr, 1);
        strcat(buff, getParenthesisStr(heap, rChild(0)));
        return buff;
    }
    return NOT_WFF;
}
const char *wff(char *str)
{
    int length = strlen(str);
    if (length == 1)
    {
        if (isOperator(str[0]))
            return NOT_WFF;
        return str;
    }
    struct Heap *heap = createHeap(length);
    char last = str[0];
    int lstOprnd = isOperator(last);
    int uniDirCnt = isUniDirOps(last);
    for (int i = 1; i < length; i++)
    {
        int op = isOperator(str[i]);
        uniDirCnt += isUniDirOps(str[i]);
        if (op == lstOprnd && !isUnary(str[i]))
            return NOT_WFF;
        if (uniDirCnt > 1)
            return NOT_WFF;

        last = str[i];
        lstOprnd = op;
    }
    for (int i = 0; i < length; i++)
    {
        addToHeap(heap, str[i]);
    }
    show(heap);
    return addParenthesis(heap);
}

int main()
{
    char s[50];
    // printf("Enter a PL ...\n");
    scanf("%s", s);
    // printf("Output WFF is...\n");
    printf("\n%s\n", wff(s));
    return 0;
}
