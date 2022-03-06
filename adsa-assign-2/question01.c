/* Q. Implement the following operations in Red Black Tree
        a. Insertion
        b. Deletion
        c. Search
        d. Display Tree
*/
// Submitted by Debonil Ghosh (M21AIE225)

#include <stdio.h>
#include <stdlib.h>

enum NodeColor
{
    RED,
    BLACK
};

struct IntervalTreeNode
{
    int low, high, max;
    enum NodeColor color;
    struct IntervalTreeNode *left, *right, *parent;
};

struct IntervalTreeNode *createTreeNode(int low, int high)
{
    struct IntervalTreeNode *tree = (struct IntervalTreeNode *)malloc(sizeof(struct IntervalTreeNode));
    tree->left = NULL;
    tree->right = NULL;
    tree->color = RED;
    tree->low = low;
    tree->high = high;
    tree->max = high;
    return tree;
}

struct IntervalTreeNode *leftRotate(struct IntervalTreeNode *x, struct IntervalTreeNode *root)
{
    struct IntervalTreeNode *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
    return root;
}

struct IntervalTreeNode *rightRotate(struct IntervalTreeNode *x, struct IntervalTreeNode *root)
{
    struct IntervalTreeNode *y = x->left;
    x->left = y->right;
    if (y->right != NULL)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->right = x;
    x->parent = y;
    return root;
}

struct IntervalTreeNode *balanceAfterInsert(struct IntervalTreeNode *root, struct IntervalTreeNode *newNode)
{
    while (newNode->parent->color == RED)
    {
        if (newNode->parent == newNode->parent->parent->right)
        {
            struct IntervalTreeNode *u = newNode->parent->parent->left;
            if (u != NULL && u->color == RED)
            {
                u->color = BLACK;
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            }
            else
            {
                if (newNode == newNode->parent->left)
                {
                    newNode = newNode->parent;
                    root = rightRotate(newNode, root);
                }
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                root = leftRotate(newNode->parent->parent, root);
            }
        }
        else
        {
            struct IntervalTreeNode *u = newNode->parent->parent->right;

            if (u != NULL && u->color == RED)
            {
                u->color = BLACK;
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            }
            else
            {
                if (newNode == newNode->parent->right)
                {
                    newNode = newNode->parent;
                    root = leftRotate(newNode, root);
                }
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                root = rightRotate(newNode->parent->parent, root);
            }
        }
        if (newNode == root)
        {
            break;
        }
    }
    root->color = BLACK;
    return root;
}

void computeMaxAfterInsert(struct IntervalTreeNode *node)
{
    if (node->parent != NULL && node->max > node->parent->max)
    {
        node->parent->max = node->max;
        computeMaxAfterInsert(node->parent);
    }
}
void computeMaxAfterDelete(struct IntervalTreeNode *node)
{
    if (node != NULL)
    {
        int newMax = node->high;
        if (node->left != NULL && node->left->max > newMax)
            newMax = node->left->max;
        if (node->right != NULL && node->right->max > newMax)
            newMax = node->right->max;
        node->max = newMax;
        if (node->parent != NULL && node->parent->max <= newMax)
            computeMaxAfterDelete(node->parent);
    }
}
struct IntervalTreeNode *treeAdd(struct IntervalTreeNode *treeNode, int low, int high)
{

    struct IntervalTreeNode *y = NULL;
    struct IntervalTreeNode *x = treeNode;

    while (x != NULL)
    {
        y = x;
        if (low < x->low)
        {
            x = x->left;
        }
        else if (low > x->low)
        {
            x = x->right;
        }
        else
            return treeNode;
    }

    struct IntervalTreeNode *node = createTreeNode(low, high);

    if (y == NULL)
    {
        node->color = BLACK;
        return node;
    }

    node->parent = y;
    if (node->low < y->low)
    {
        y->left = node;
    }
    else
    {
        y->right = node;
    }

    if (node->parent->parent == NULL)
    {
        return treeNode;
    }
    treeNode = balanceAfterInsert(treeNode, node);
    computeMaxAfterInsert(node);
    return treeNode;
}
struct IntervalTreeNode *searchTreeNode(struct IntervalTreeNode *tree, struct IntervalTreeNode *root, int searchVal)
{
    if (root == NULL)
    {
        printf("EMPTY\n");
        return tree;
    }
    if (tree == NULL)
    {
        printf("ABSENT\n");
        return tree;
    }
    if (tree->low == searchVal)
    {
        printf("PRESENT\n");
        return tree;
    }

    else if (tree->low > searchVal)
        return searchTreeNode(tree->left, root, searchVal);
    else if (tree->low < searchVal)
        return searchTreeNode(tree->right, root, searchVal);
    return NULL;
}

struct IntervalTreeNode *smallest(struct IntervalTreeNode *tree)
{
    while (tree && tree->left != NULL)
        tree = tree->left;
    return tree;
}

struct IntervalTreeNode *replace(struct IntervalTreeNode *u, struct IntervalTreeNode *v, struct IntervalTreeNode *root)
{
    if (u->parent == NULL)
    {
        root = v;
    }
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != NULL)
        v->parent = u->parent;
    return root;
}
int isBlack(struct IntervalTreeNode *x)
{
    return x == NULL || x->color == BLACK;
}
struct IntervalTreeNode *balanceAfterDelete(struct IntervalTreeNode *x, struct IntervalTreeNode *xParent, struct IntervalTreeNode *root)
{
    struct IntervalTreeNode *s;
    while (x != root && isBlack(x))
    {
        if (x == xParent->left)
        {
            s = xParent->right;
            if (s->color == RED)
            {
                s->color = BLACK;
                xParent->color = RED;
                root = leftRotate(xParent, root);
                s = xParent->right;
            }

            if (isBlack(s->left) && isBlack(s->right))
            {
                s->color = RED;
                x = xParent;
            }
            else
            {
                if (isBlack(s->right))
                {
                    s->left->color = BLACK;
                    s->color = RED;
                    root = rightRotate(s, root);
                    s = xParent->right;
                }

                s->color = xParent->color;
                xParent->color = BLACK;
                s->right->color = BLACK;
                root = leftRotate(xParent, root);
                x = root;
            }
        }
        else
        {
            s = xParent->left;
            if (s->color == RED)
            {
                s->color = BLACK;
                xParent->color = RED;
                root = rightRotate(xParent, root);
                s = xParent->left;
            }

            if (isBlack(s->left) && isBlack(s->right))
            {
                s->color = RED;
                x = xParent;
            }
            else
            {
                if (isBlack(s->left))
                {
                    s->right->color = BLACK;
                    s->color = RED;
                    root = leftRotate(s, root);
                    s = xParent->left;
                }

                s->color = xParent->color;
                xParent->color = BLACK;
                s->left->color = BLACK;
                root = rightRotate(xParent, root);
                x = root;
            }
        }
        if (x != NULL)
            xParent = x->parent;
    }
    x->color = BLACK;
    return root;
}
struct IntervalTreeNode *treeRemove(struct IntervalTreeNode *root, int searchValLeft, int searchValRight)
{
    if (root == NULL)
    {
        printf("EMPTY\n");
        return root;
    }
    struct IntervalTreeNode *z = NULL, *node = root, *x, *y, *xparent;
    while (node != NULL)
    {
        if (node->low == searchValLeft)
        {
            z = node;
        }

        if (node->low <= searchValLeft)
        {
            node = node->right;
        }
        else
        {
            node = node->left;
        }
    }

    if (z == NULL)
    {
        printf("ABSENT\n");
        return root;
    }

    y = z;
    enum NodeColor yOriginalColor = y->color;
    if (z->left == NULL)
    {
        x = z->right;
        root = replace(z, z->right, root);
        xparent = z->parent;
    }
    else if (z->right == NULL)
    {
        x = z->left;
        root = replace(z, z->left, root);
        xparent = z->parent;
    }
    else
    {
        y = smallest(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z)
        {
            xparent = y;
        }
        else
        {
            xparent = y->parent;
            root = replace(y, y->right, root);
            y->right = z->right;
            y->right->parent = y;
        }

        root = replace(z, y, root);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (yOriginalColor == BLACK)
    {
        // root = balanceAfterDelete(x, xparent, root);
    }
    computeMaxAfterDelete(xparent);
    free(z);
    return root;
}
void inorderTravers(struct IntervalTreeNode *tree)
{
    if (tree != NULL)
    {
        inorderTravers(tree->left);
        // printf("(%d,%d)|%d|%c ", tree->low, tree->high, tree->max, tree->color ? 'B' : 'R');
        printf("%d %d %d\n", tree->low, tree->high, tree->max);
        inorderTravers(tree->right);
    }
}
void preorderTravers(struct IntervalTreeNode *tree)
{
    if (tree != NULL)
    {
        printf("\t[ %d ] ", tree->low);
        preorderTravers(tree->left);
        preorderTravers(tree->right);
    }
}
void postorderTravers(struct IntervalTreeNode *tree)
{
    if (tree != NULL)
    {
        postorderTravers(tree->left);
        postorderTravers(tree->right);
        printf("\t[ %d ] ", tree->low);
    }
}

int main()
{
    int option = -1, tmp, tmp2;
    struct IntervalTreeNode *tree = NULL;
    while (option != 4)
    {
        // printf("\nEnter \n 1. to Insert \n 2. to Delete \n 3. to Search elements\n 4. to See Inorder traversal\n 5. to See Preorder traversal\n 6. to See Postorder traversal\n 0. to Exit\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            // printf("Enter value to insert:\n");
            scanf("%d", &tmp);
            scanf("%d", &tmp2);
            tree = treeAdd(tree, tmp, tmp2);
            break;
        case 2:
            // printf("Enter value to remove:\n");
            if (tree == NULL)
            {
                printf("EMPTY\n");
                break;
            }
            scanf("%d", &tmp);
            scanf("%d", &tmp2);
            tree = treeRemove(tree, tmp, tmp2);
            break;
        case 3:
            inorderTravers(tree);
            // printf("\n");
            break;
        case 4:
            // printf("\n");
            break;

        default:
            // printf("Enter valid option..\n");
            break;
        }
    }
    return 0;
}
