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
#include <stdlib.h>

static const char OPS_PRECDNCE[] = "~>|&!";
static const char BI_DIR_OPS[] = "~&|";
static const char UNI_DIR_OPS[] = ">";
static const char UNIARY_OPS[] = "!";

static const char PAREN_OPEN = '(';
static const char PAREN_CLOSE = ')';

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
int strlength(const char *s)
{
    int i = 0;
    while (*(s + i) != '\0')
        i++;
    return i;
}
const char *concat(char *s1, const char *s2)
{
    int i = 0, j = 0;
    while (*(s1 + i) != '\0')
        i++;
    while (*(s2 + j) != '\0')
        s1[i + j++] = s2[j];
    s1[i + j] = '\0';
    return s1;
}
const char *concatchar(char *s1, const char c)
{
    int i = 0, j = 0;
    while (*(s1 + i) != '\0')
        i++;
    s1[i] = c;
    s1[i + 1] = '\0';
    return s1;
}
int treeComp(char a, char b)
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
struct TreeNode
{
    char val;
    struct TreeNode *left, *right;
    int size;
};

struct TreeNode *createTreeNode(char val)
{
    struct TreeNode *tree = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    tree->left = NULL;
    tree->right = NULL;
    tree->val = val;
    tree->size = 1;
    return tree;
}
struct TreeNode *treeAdd(struct TreeNode *treeNode, char val)
{
    if (treeNode == NULL)
    {
        return createTreeNode(val);
    }
    else if (treeComp(treeNode->val, val))
    {
        struct TreeNode *newNode = createTreeNode(val);
        newNode->left = treeNode;
        newNode->size += treeNode->size;
        return newNode;
    }
    else
    {
        treeNode->right = treeAdd(treeNode->right, val);
        treeNode->size++;
        return treeNode;
    }
}
const char *getParenthesisStr(struct TreeNode *tree)
{
    char *buff = "";
    if (tree != NULL)
    {
        buff = (char *)calloc((tree->size * 3), sizeof(char));
        char op = tree->val;
        if (isOperator(op))
        {
            concatchar(buff, PAREN_OPEN);
            concat(buff, getParenthesisStr(tree->left));
            concatchar(buff, op);
            concat(buff, getParenthesisStr(tree->right));
            concatchar(buff, PAREN_CLOSE);
        }
        else
        {
            concatchar(buff, op);
        }
    }

    return buff;
}
const char *addParenthesis(struct TreeNode *tree)
{
    if (tree != NULL && tree->size > 0)
    {
        char *buff = (char *)calloc((tree->size * 3), sizeof(char));
        concat(buff, getParenthesisStr(tree->left));
        concatchar(buff, tree->val);
        concat(buff, getParenthesisStr(tree->right));
        return buff;
    }
    return NOT_WFF;
}
const char *wff(char *str)
{
    int length = strlength(str);
    if (length == 1)
    {
        if (isOperator(str[0]))
            return NOT_WFF;
        return str;
    }
    char last = str[0];
    int lstOprnd = isOperator(last);
    int uniDirCnt = isUniDirOps(last);
    struct TreeNode *tree = treeAdd(NULL, last);
    for (int i = 1; i < length; i++)
    {
        int op = isOperator(str[i]);
        if ((op == lstOprnd) != isUnary(str[i]))
            return NOT_WFF;
        uniDirCnt += isUniDirOps(str[i]);
        if (uniDirCnt > 1)
            return NOT_WFF;
        tree = treeAdd(tree, str[i]);
        last = str[i];
        lstOprnd = op;
    }
    return addParenthesis(tree);
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
