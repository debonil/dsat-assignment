/* Q. Implement the following operations in Red Black Tree
        a. Insertion
        b. Deletion
        c. Search
        d. Display Tree
*/
// Submitted by Debonil Ghosh (M21AIE225)

#include <stdio.h>
#include <stdlib.h>

struct RedBlackTreeNode
{
    int val;
    int color;
    struct RedBlackTreeNode *left, *right;
};

struct RedBlackTreeNode *createTreeNode(int val)
{
    struct RedBlackTreeNode *tree = (struct RedBlackTreeNode *)malloc(sizeof(struct RedBlackTreeNode));
    tree->left = NULL;
    tree->right = NULL;
    tree->val = val;
    return tree;
}

struct RedBlackTreeNode *treeAdd(struct RedBlackTreeNode *treeNode, int val)
{
    if (treeNode == NULL)
    {
        printf("\t\t      [ %d ] added to the Tree! \n", val);
        return createTreeNode(val);
    }

    if (val < treeNode->val)
        treeNode->left = treeAdd(treeNode->left, val);
    else
        treeNode->right = treeAdd(treeNode->right, val);

    return treeNode;
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
