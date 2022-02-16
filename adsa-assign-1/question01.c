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

struct RedBlackTreeNode
{
    int val;
    enum NodeColor color;
    struct RedBlackTreeNode *left, *right, *parent;
};

struct RedBlackTreeNode *createTreeNode(int val)
{
    struct RedBlackTreeNode *tree = (struct RedBlackTreeNode *)malloc(sizeof(struct RedBlackTreeNode));
    tree->left = NULL;
    tree->right = NULL;
    tree->color = RED;
    tree->val = val;
    return tree;
}

struct RedBlackTreeNode *leftRotate(struct RedBlackTreeNode *x, struct RedBlackTreeNode *root)
{
    struct RedBlackTreeNode *y = x->right;
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

struct RedBlackTreeNode *rightRotate(struct RedBlackTreeNode *x, struct RedBlackTreeNode *root)
{
    struct RedBlackTreeNode *y = x->left;
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

struct RedBlackTreeNode *balanceAfterInsert(struct RedBlackTreeNode *root, struct RedBlackTreeNode *newNode)
{
    while (newNode->parent->color == RED)
    {
        if (newNode->parent == newNode->parent->parent->right)
        {
            struct RedBlackTreeNode *u = newNode->parent->parent->left;
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
            struct RedBlackTreeNode *u = newNode->parent->parent->right;

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
struct RedBlackTreeNode *treeAdd(struct RedBlackTreeNode *treeNode, int val)
{

    struct RedBlackTreeNode *y = NULL;
    struct RedBlackTreeNode *x = treeNode;

    while (x != NULL)
    {
        y = x;
        if (val < x->val)
        {
            x = x->left;
        }
        else if (val > x->val)
        {
            x = x->right;
        }
        else
            return treeNode;
    }

    struct RedBlackTreeNode *node = createTreeNode(val);

    if (y == NULL)
    {
        node->color = BLACK;
        return node;
    }

    node->parent = y;
    if (node->val < y->val)
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

    return balanceAfterInsert(treeNode, node);
}
struct RedBlackTreeNode *searchTreeNode(struct RedBlackTreeNode *tree, int searchVal)
{
    if (tree == NULL)
    {
        printf("NO\n");
        return tree;
    }
    if (tree->val == searchVal)
    {
        printf("YES\n");
        return tree;
    }

    else if (tree->val > searchVal)
        return searchTreeNode(tree->left, searchVal);
    else if (tree->val < searchVal)
        return searchTreeNode(tree->right, searchVal);
    return NULL;
}

struct RedBlackTreeNode *smallest(struct RedBlackTreeNode *tree)
{
    while (tree && tree->left != NULL)
        tree = tree->left;
    return tree;
}
struct RedBlackTreeNode *treeRemove(struct RedBlackTreeNode *tree, int searchVal)
{
    if (tree == NULL)
    {
        printf("\t\t      [ %d ] NOT found in Tree! \n", searchVal);
        return tree;
    }

    else if (tree->val > searchVal)
        tree->left = treeRemove(tree->left, searchVal);
    else if (tree->val < searchVal)
        tree->right = treeRemove(tree->right, searchVal);
    else if (tree->val == searchVal)
    {
        printf("\t\t      [ %d ] found in Tree! \n", tree->val);
        if (tree->left == NULL && tree->right == NULL)
        {
            free(tree);
            return NULL;
        }
        else if (tree->right == NULL)
        {
            struct RedBlackTreeNode *tmp = tree->left;
            free(tree);
            return tmp;
        }
        else if (tree->left == NULL)
        {
            struct RedBlackTreeNode *tmp = tree->right;
            free(tree);
            return tmp;
        }
        else
        {
            struct RedBlackTreeNode *tmp = smallest(tree->right);
            tree->val = tmp->val;
            tree->right = treeRemove(tree->right, tmp->val);
        }
        return tree;
    }
    else
    {
        printf("\t\t      [ %d ] not found in the Tree! \n", searchVal);
    }
    return tree;
}
void inorderTravers(struct RedBlackTreeNode *tree)
{
    if (tree != NULL)
    {
        inorderTravers(tree->left);
        printf("%d%c ", tree->val, tree->color ? 'B' : 'R');
        inorderTravers(tree->right);
    }
}
void preorderTravers(struct RedBlackTreeNode *tree)
{
    if (tree != NULL)
    {
        printf("\t[ %d ] ", tree->val);
        preorderTravers(tree->left);
        preorderTravers(tree->right);
    }
}
void postorderTravers(struct RedBlackTreeNode *tree)
{
    if (tree != NULL)
    {
        postorderTravers(tree->left);
        postorderTravers(tree->right);
        printf("\t[ %d ] ", tree->val);
    }
}

int main()
{
    int option = -1, tmp;
    struct RedBlackTreeNode *tree = NULL;
    while (option != 5)
    {
        // printf("\nEnter \n 1. to Insert \n 2. to Delete \n 3. to Search elements\n 4. to See Inorder traversal\n 5. to See Preorder traversal\n 6. to See Postorder traversal\n 0. to Exit\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            // printf("Enter value to insert:\n");
            scanf("%d", &tmp);
            tree = treeAdd(tree, tmp);
            break;
        case 2:
            // printf("Enter value to remove:\n");
            scanf("%d", &tmp);
            tree = treeRemove(tree, tmp);
            break;
        case 3:
            // printf("Enter value to search:\n");
            scanf("%d", &tmp);
            searchTreeNode(tree, tmp);
            break;
        case 4:
            inorderTravers(tree);
            break;
        case 5:
            printf("\n");
            break;

        default:
            printf("Enter valid option..\n");
            break;
        }
    }
    return 0;
}
