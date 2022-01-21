// Q10. Implement the Singly Linked list data structure from scratch and perform
//  insertion ( at head, at middle and at tail), deletion (at head, at middle and at tail)
//  and search element operations. After each operation, display the elements of the
//  linked list.
// Submitted by Debonil Ghosh (M21AIE225)

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int val;
    struct Node *next;
};

struct Node *createNode(int val)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->val = val;
    return node;
}

struct Node *getTailNode(struct Node *node)
{
    struct Node *n = node;
    while (n->next != NULL)
    {
        n = n->next;
    }
    return n;
}

struct Node *getNodeByPosition(struct Node *node, int position)
{
    struct Node *n = node;
    while (n->next != NULL && position--)
    {
        n = n->next;
    }
    if (position > -1)
        printf("\t\t      Position is out of list, last node retuned! \n");
    return n;
}
struct Node *getNodeByValue(struct Node *node, int val)
{
    int i = 0;
    struct Node *n = node;
    while (n != NULL && n->val != val)
    {
        n = n->next;
        i++;
    }
    if (n)
        printf("\t\t    [ %d ] found at position [ %d ]! \n", val, i);
    else
        printf("\t\t    [ %d ] NOT found in the List! \n", val);
    return n;
}

struct Node *addNodeAtHead(struct Node *node, int val)
{
    struct Node *newNode = createNode(val);
    newNode->next = node;
    printf("\t\t      [ %d ] added to the List Head! \n", val);
    return newNode;
}

struct Node *addNodeAtTail(struct Node *node, int val)
{
    struct Node *newNode = createNode(val);
    struct Node *tailNode = getTailNode(node);
    tailNode->next = newNode;
    printf("\t\t      [ %d ] added to the List Tail! \n", val);
    return node;
}

struct Node *addNodeAtPosition(struct Node *node, int val, int pos)
{
    struct Node *newNode = createNode(val);
    struct Node *tailNode = getNodeByPosition(node, pos - 1);
    newNode->next = tailNode->next;
    tailNode->next = newNode;
    printf("\t\t      [ %d ] added to the List at position [ %d ] ! \n", val, pos);
    return node;
}

struct Node *removeNodeAtHead(struct Node *node)
{
    struct Node *nextNode = node->next;
    int val = node->val;
    free(node);
    printf("\t\t      [ %d ] removed from the List Head! \n", val);
    return nextNode;
}

struct Node *removeNodeAtTail(struct Node *node)
{
    if (node != NULL && node->next != NULL)
        node->next = removeNodeAtTail(node->next);
    else if (node != NULL)
    {
        int val = node->val;
        free(node);
        printf("\t\t      [ %d ] removed from the List Tail! \n", val);
        return NULL;
    }
    return node;
}

struct Node *removeNodeAtPosition(struct Node *node, int pos)
{
    struct Node *tailNode = getNodeByPosition(node, pos - 1);
    struct Node *nodeToDel = tailNode->next;
    int val = nodeToDel->val;
    tailNode->next = nodeToDel->next;
    free(nodeToDel);
    printf("\t\t      [ %d ] removed from the List position [ %d ] ! \n", val, pos);
    return node;
}
void showList(struct Node *node)
{
    printf("List trace : \n");
    if (node != NULL)
    {
        printf("\t\t\t ->");
        struct Node *n = node;
        while (n != NULL)
        {
            printf(" [ %d ] ->", n->val);
            n = n->next;
        }
        printf("| \n");
    }
    else
    {
        printf("\t\t\tList empty!! \n");
    }
}

int main()
{
    int option = -1, tmp, pos = -1;
    struct Node *node = NULL;
    while (option != 0)
    {
        printf("\nEnter \n 1. to Insert (head)\n 2. to Insert (middle)\n 3. to Insert (tail)\n 4. to Delete (head)\n 5. to Delete (middle)\n 6. to Delete (tail)\n 7. to Search\n 8. to See all elements\n 0. to Exit\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            printf("Enter value to insert At Head:\n");
            scanf("%d", &tmp);
            node = addNodeAtHead(node, tmp);
            showList(node);
            break;
        case 2:
            printf("Enter position to insert at:\n");
            scanf("%d", &pos);
            printf("Enter value to insert At position [ %d ]:\n", pos);
            scanf("%d", &tmp);
            node = addNodeAtPosition(node, tmp, pos);
            showList(node);
            break;
        case 3:
            printf("Enter value to insert At Tail:\n");
            scanf("%d", &tmp);
            node = addNodeAtTail(node, tmp);
            showList(node);
            break;
        case 4:
            node = removeNodeAtHead(node);
            showList(node);
            break;
        case 5:
            printf("Enter position to delete at:\n");
            scanf("%d", &tmp);
            node = removeNodeAtPosition(node, tmp);
            showList(node);
            break;
        case 6:
            node = removeNodeAtTail(node);
            showList(node);
            break;
        case 7:
            printf("Enter Value to search :\n");
            scanf("%d", &tmp);
            getNodeByValue(node, tmp);
            showList(node);
            break;
        case 8:
            showList(node);
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
