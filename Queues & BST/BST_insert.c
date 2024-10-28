#include <stdio.h>
#include <stdlib.h>

//   Given a Binary Search Tree
//
//         6
//        / \
//       4   7
//      / \   \
//     3   5   9

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

void PreOrder(struct Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

void PostOrder(struct Node *root)
{
    if (root != NULL)
    {
        PostOrder(root->left);
        PostOrder(root->right);
        printf("%d ", root->data);
    }
}

void InOrder(struct Node *root)
{
    if (root != NULL)
    {
        InOrder(root->left);
        printf("%d ", root->data);
        InOrder(root->right);
    }
}

struct Node *create_node(int data)
{
    struct Node *n;
    n = (struct Node *)malloc(sizeof(struct Node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void free_tree(struct Node *root)
{
    if(root != NULL)
    {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

void insert(struct Node *root,int key)
{
    struct Node *prev=NULL;
    while(root!=NULL)
    {
        prev=root;
        if(root->data==key)
        {
            printf("\nDuplicate Element not Allowed!\n");
            return;
        }
        else if(root->data < key)
        {
            root=root->right;
        }
        else
        {
            root=root->left;
        }
    }

    struct Node *new_node=create_node(key);
    if(prev->data<key)
    {
        prev->right=new_node;
    }
    else
    {
        prev->left=new_node;
    }
}



int main()
{
//         6
//        / \
//       4   7
//      / \   \
//     3   5   9
    struct Node *root = create_node(6);
    struct Node *r1 = create_node(4);
    struct Node *r3 = create_node(3);
    struct Node *r4 = create_node(5);
    struct Node *r5 = create_node(7);
    struct Node *r6 = create_node(9);

    // establishing links
    root->left=r1;
    root->right=r5;
    r1->left=r3;
    r1->right=r4;
    r5->right=r6;


    printf("The InOrder Traversal of Binary Search Tree is: \n");
    InOrder(root);
    
    insert(root,10);
    
    printf("\nAfter Insertion BST is: \n");
    InOrder(root);
    free_tree(root);
    return 0;
}