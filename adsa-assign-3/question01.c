/* 1) Implement the following operations in B Tree :

        a. Insertion. [1]
        b. Deletion. [2]
        c. Inorder Traversal. [3]

    Sample case :
        Input:
            3
            10
            1
            18 20 11 15 23 8 9 10 16 17
            3
            2
            20
            3
            4
        Output:
            8 9 10 11 15 16 17 18 20 23
            8 9 10 11 15 16 17 18 23
*/
// Submitted by Debonil Ghosh (M21AIE225)

#include <stdio.h>
#include <stdlib.h>

struct BTree
{
    int order;
    struct BTreeNode *root;
};

struct BTreeNode
{
    int size, isLeaf, *keys;
    struct BTreeNode **children;
};

struct BTreeNode *createBTreeNode(struct BTree *tree)
{
    struct BTreeNode *node = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    node->size = 0;
    node->isLeaf = 0;
    node->keys = (int *)calloc(2 * tree->order - 1, sizeof(int));
    node->children = (struct BTreeNode **)calloc(2 * tree->order, sizeof(struct BTreeNode *));
    return node;
}

struct BTree *createBTree(int order)
{
    struct BTree *tree = (struct BTree *)malloc(sizeof(struct BTree));
    tree->order = order;
    tree->root = createBTreeNode(tree);
    tree->root->isLeaf = 1;
    return tree;
}
void splitNode(struct BTree *tree, struct BTreeNode *x, int pos, struct BTreeNode *y)
{
    int T = tree->order; // / 2 + tree->order % 2;
    struct BTreeNode *z = createBTreeNode(tree);
    z->isLeaf = y->isLeaf;
    z->size = T - 1;
    for (int j = 0; j < T - 1; j++)
    {
        z->keys[j] = y->keys[j + T];
    }
    if (!y->isLeaf)
    {
        for (int j = 0; j < T; j++)
        {
            z->children[j] = y->children[j + T];
        }
    }
    y->size = T - 1;
    for (int j = x->size; j >= pos + 1; j--)
    {
        x->children[j + 1] = x->children[j];
    }
    x->children[pos + 1] = z;

    for (int j = x->size - 1; j >= pos; j--)
    {
        x->keys[j + 1] = x->keys[j];
    }
    x->keys[pos] = y->keys[T - 1];
    x->size = x->size + 1;
}

void insertValueIntoTree(struct BTree *tree, struct BTreeNode *node, int value)
{
    if (node->isLeaf)
    {
        int i = 0;
        for (i = node->size - 1; i >= 0 && value < node->keys[i]; i--)
        {
            node->keys[i + 1] = node->keys[i];
        }
        node->keys[i + 1] = value;
        node->size = node->size + 1;
    }
    else
    {
        int i = 0;
        for (i = node->size - 1; i >= 0 && value < node->keys[i]; i--)
        {
        };
        i++;
        struct BTreeNode *tmp = node->children[i];
        if (tmp->size == 2 * tree->order - 1)
        {
            splitNode(tree, node, i, tmp);
            if (value > node->keys[i])
            {
                i++;
            }
        }
        insertValueIntoTree(tree, node->children[i], value);
    }
}
void treeAdd(struct BTree *tree, int val)
{

    struct BTreeNode *r = tree->root;
    if (r->size == 2 * tree->order - 1)
    {
        struct BTreeNode *s = createBTreeNode(tree);
        tree->root = s;
        s->isLeaf = 0;
        s->size = 0;
        s->children[0] = r;
        splitNode(tree, s, 0, r);
        insertValueIntoTree(tree, s, val);
    }
    else
    {
        insertValueIntoTree(tree, r, val);
    }
}
void searchTreeNode(struct BTree *tree, int searchVal)
{
    if (tree->root == NULL || tree->root->size == 0)
    {
        printf("EMPTY\n");
        return;
    }
    struct BTreeNode *node = tree->root;
    while (node)
    {
        int i = 0;
        for (; i < node->size; i++)
        {
            if (node->keys[i] == searchVal)
            {
                printf("PRESENT\n");
                return;
            }
            if (node->keys[i] > searchVal)
                break;
        }
        if (node->isLeaf)
        {
            printf("ABSENT\n");
            return;
        }
        else
            node = node->children[i];
    }
    return;
}

struct BTreeNode *smallest(struct BTreeNode *tree)
{
    while (tree && !tree->isLeaf)
        tree = tree->children[0];
    return tree;
}

struct BTree *treeRemove(struct BTree *root, int searchValLeft)
{
    if (root == NULL)
    {
        printf("EMPTY\n");
        return root;
    }

    return root;
}
void inorderTravers(struct BTreeNode *node)
{
    if (node != NULL)
    {
        for (int i = 0; i < node->size; i++)
        {
            inorderTravers(node->children[i]);
            printf("%d ", node->keys[i]);
        }
        inorderTravers(node->children[node->size]);
    }
}
void preorderTravers(struct BTreeNode *node)
{
    if (node != NULL)
    {
        for (int i = 0; i < node->size; i++)
        {
            printf("[ %d ] ", node->keys[i]);
            preorderTravers(node->children[i]);
        }
        preorderTravers(node->children[node->size]);
    }
}
void postorderTravers(struct BTreeNode *node)
{
    if (node != NULL)
    {
        postorderTravers(node->children[0]);
        for (int i = 0; i < node->size; i++)
        {
            postorderTravers(node->children[i + 1]);
            printf("[ %d ] ", node->keys[i]);
        }
    }
}

int main()
{
    int option = -1, tmp, n;
    scanf("%d", &tmp);
    struct BTree *tree = createBTree(tmp);
    scanf("%d", &n);
    while (option != 4)
    {
        // printf("\nEnter \n 1. to Insert \n 2. to Delete \n 3. to Search elements\n 4. to See Inorder traversal\n 5. to See Preorder traversal\n 6. to See Postorder traversal\n 0. to Exit\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            // printf("Enter value to insert:\n");
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &tmp);
                treeAdd(tree, tmp);
            }
            break;
        case 2:
            // printf("Enter value to remove:\n");
            if (tree == NULL)
            {
                printf("EMPTY\n");
                break;
            }
            scanf("%d", &tmp);
            // tree = treeRemove(tree, tmp);
            break;
        case 3:
            inorderTravers(tree->root);
            printf("\n");
            break;

        default:
            // printf("Enter valid option..\n");
            break;
        }
    }
    return 0;
}
