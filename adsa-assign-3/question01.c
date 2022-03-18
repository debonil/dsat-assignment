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
void splitNode(struct BTree *tree, struct BTreeNode *parent, int splitIndex, struct BTreeNode *child)
{
    struct BTreeNode *anotherChild = createBTreeNode(tree);
    anotherChild->isLeaf = child->isLeaf;
    anotherChild->size = tree->order - 1;
    for (int j = 0; j < tree->order - 1; j++)
    {
        anotherChild->keys[j] = child->keys[j + tree->order];
    }
    if (!child->isLeaf)
    {
        for (int j = 0; j < tree->order; j++)
        {
            anotherChild->children[j] = child->children[j + tree->order];
        }
    }
    child->size = tree->order - 1;
    for (int j = parent->size; j >= splitIndex + 1; j--)
    {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[splitIndex + 1] = anotherChild;

    for (int j = parent->size - 1; j >= splitIndex; j--)
    {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[splitIndex] = child->keys[tree->order - 1];
    parent->size = parent->size + 1;
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
        s->children[0] = r;
        splitNode(tree, s, 0, r);
        insertValueIntoTree(tree, s, val);
    }
    else
    {
        insertValueIntoTree(tree, r, val);
    }
}
struct BTreeNode *searchTreeNode(struct BTree *tree, int searchVal)
{
    if (tree->root == NULL || tree->root->size == 0)
    {
        // printf("EMPTY\n");
        return NULL;
    }
    struct BTreeNode *node = tree->root;
    while (node)
    {
        int i = 0;
        for (; i < node->size; i++)
        {
            if (node->keys[i] == searchVal)
            {
                // printf("PRESENT\n");
                return node;
            }
            if (node->keys[i] > searchVal)
                break;
        }
        if (node->isLeaf)
        {
            // printf("ABSENT\n");
            return NULL;
        }
        else
            node = node->children[i];
    }
    return NULL;
}

int searchKeyIndex(struct BTreeNode *node, int key)
{
    for (int i = 0; i < node->size; i++)
    {
        if (node->keys[i] == key)
        {
            return i;
        }
    }
    return -1;
}

struct BTreeNode *smallest(struct BTreeNode *tree)
{
    while (tree && !tree->isLeaf)
        tree = tree->children[0];
    return tree;
}
void removeNode(struct BTree *tree, struct BTreeNode *node, int key)
{
    int keyIndex = searchKeyIndex(node, key);
    if (keyIndex != -1)
    {
        if (node->isLeaf)
        {
            int i = 0;
            for (i = 0; i < node->size && node->keys[i] != key; i++)
            {
            };
            for (; i < node->size; i++)
            {
                if (i != 2 * tree->order - 2)
                {
                    node->keys[i] = node->keys[i + 1];
                }
            }
            node->size--;
            return;
        }
        if (!node->isLeaf)
        {

            struct BTreeNode *pred = node->children[keyIndex];
            int predKey = 0;
            if (pred->size >= tree->order)
            {
                while (1)
                {
                    if (pred->isLeaf)
                    {
                        predKey = pred->keys[pred->size - 1];
                        break;
                    }
                    else
                    {
                        pred = pred->children[pred->size];
                    }
                }
                removeNode(tree, pred, predKey);
                node->keys[keyIndex] = predKey;
                return;
            }

            struct BTreeNode *nextNode = node->children[keyIndex + 1];
            if (nextNode->size >= tree->order)
            {
                int nextKey = nextNode->keys[0];
                if (!nextNode->isLeaf)
                {
                    nextNode = nextNode->children[0];
                    while (1)
                    {
                        if (nextNode->isLeaf)
                        {
                            nextKey = nextNode->keys[nextNode->size - 1];
                            break;
                        }
                        else
                        {
                            nextNode = nextNode->children[nextNode->size];
                        }
                    }
                }
                removeNode(tree, nextNode, nextKey);
                node->keys[keyIndex] = nextKey;
                return;
            }

            int temp = pred->size + 1;
            pred->keys[pred->size++] = node->keys[keyIndex];
            for (int i = 0, j = pred->size; i < nextNode->size; i++)
            {
                pred->keys[j++] = nextNode->keys[i];
                pred->size++;
            }
            for (int i = 0; i < nextNode->size + 1; i++)
            {
                pred->children[temp++] = nextNode->children[i];
            }

            node->children[keyIndex] = pred;
            for (int i = keyIndex; i < node->size; i++)
            {
                if (i != 2 * tree->order - 2)
                {
                    node->keys[i] = node->keys[i + 1];
                }
            }
            for (int i = keyIndex + 1; i < node->size + 1; i++)
            {
                if (i != 2 * tree->order - 1)
                {
                    node->children[i] = node->children[i + 1];
                }
            }
            node->size--;
            if (node->size == 0)
            {
                if (node == tree->root)
                {
                    tree->root = node->children[0];
                }
                node = node->children[0];
            }
            removeNode(tree, pred, key);
            return;
        }
    }
    else
    {
        for (keyIndex = 0; keyIndex < node->size; keyIndex++)
        {
            if (node->keys[keyIndex] > key)
            {
                break;
            }
        }
        struct BTreeNode *tmp = node->children[keyIndex];
        if (tmp->size >= tree->order)
        {
            removeNode(tree, tmp, key);
            return;
        }
        else
        {
            struct BTreeNode *nb = NULL;
            int divider = -1;

            if (keyIndex != node->size && node->children[keyIndex + 1]->size >= tree->order)
            {
                divider = node->keys[keyIndex];
                nb = node->children[keyIndex + 1];
                node->keys[keyIndex] = nb->keys[0];
                tmp->keys[tmp->size++] = divider;
                tmp->children[tmp->size] = nb->children[0];
                for (int i = 1; i < nb->size; i++)
                {
                    nb->keys[i - 1] = nb->keys[i];
                }
                for (int i = 1; i <= nb->size; i++)
                {
                    nb->children[i - 1] = nb->children[i];
                }
                nb->size--;
                removeNode(tree, tmp, key);
                return;
            }
            else if (keyIndex != 0 && node->children[keyIndex - 1]->size >= tree->order)
            {

                divider = node->keys[keyIndex - 1];
                nb = node->children[keyIndex - 1];
                node->keys[keyIndex - 1] = nb->keys[nb->size - 1];
                struct BTreeNode *child = nb->children[nb->size];
                nb->size--;

                for (int i = tmp->size; i > 0; i--)
                {
                    tmp->keys[i] = tmp->keys[i - 1];
                }
                tmp->keys[0] = divider;
                for (int i = tmp->size + 1; i > 0; i--)
                {
                    tmp->children[i] = tmp->children[i - 1];
                }
                tmp->children[0] = child;
                tmp->size++;
                removeNode(tree, tmp, key);
                return;
            }
            else
            {
                struct BTreeNode *lt = NULL;
                struct BTreeNode *rt = NULL;
                int last = 0;
                if (keyIndex != node->size)
                {
                    divider = node->keys[keyIndex];
                    lt = node->children[keyIndex];
                    rt = node->children[keyIndex + 1];
                }
                else
                {
                    divider = node->keys[keyIndex - 1];
                    rt = node->children[keyIndex];
                    lt = node->children[keyIndex - 1];
                    last = 1;
                    keyIndex--;
                }
                for (int i = keyIndex; i < node->size - 1; i++)
                {
                    node->keys[i] = node->keys[i + 1];
                }
                for (int i = keyIndex + 1; i < node->size; i++)
                {
                    node->children[i] = node->children[i + 1];
                }
                node->size--;
                lt->keys[lt->size++] = divider;

                for (int i = 0, j = lt->size; i < rt->size + 1; i++, j++)
                {
                    if (i < rt->size)
                    {
                        lt->keys[j] = rt->keys[i];
                    }
                    lt->children[j] = rt->children[i];
                }
                lt->size += rt->size;
                if (node->size == 0)
                {
                    if (node == tree->root)
                    {
                        tree->root = node->children[0];
                    }
                    node = node->children[0];
                }
                removeNode(tree, lt, key);
                return;
            }
        }
    }
}

void treeRemove(struct BTree *tree, int searchVal)
{
    if (tree == NULL)
    {
        printf("EMPTY\n");
        return;
    }
    if (searchTreeNode(tree, searchVal))
    {
        removeNode(tree, tree->root, searchVal);
    }
    return;
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
            treeRemove(tree, tmp);
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
