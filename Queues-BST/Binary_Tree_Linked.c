#include <stdio.h>
#include <stdlib.h>

//      4
//     / \
//    5   9
//   / \   \
//  3   1   8
//
// Given a binary tree we will implement it and traverse it in different ways

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

// function for creating node
struct Node *create_node(int data)
{
    struct Node *n;
    n = (struct Node *)malloc(sizeof(struct Node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;

    return n;
}

// PreOrder Traversal   Root -> left -> right
void PreOrder(struct Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}


// PostOrder Traversal  left -> right -> Root
void PostOrder(struct Node *root)
{
    if(root!=NULL)
    {
        PostOrder(root->left);
        PostOrder(root->right);
        printf("%d ",root->data);
    }
}


// InOrder Traversal   left -> Root -> right
void InOrder(struct Node *root)
{
    if(root!=NULL)
    {
        InOrder(root->left);
        printf("%d ",root->data);
        InOrder(root->right);
    }
}

// function to deallocate memory
void free_tree(struct Node *root)
{
    if (root == NULL)
        return;

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main()
{
    struct Node *root = create_node(4);
    struct Node *r1 = create_node(5);
    struct Node *r2 = create_node(9);
    struct Node *r3 = create_node(3);
    struct Node *r4 = create_node(1);
    struct Node *r5 = create_node(8);

    root->left = r1;
    root->right = r2;
    
    r1->left = r3;
    r1->right = r4;

    r2->right = r5;
    
    printf("The Pre Order Traversal Will be: \n");
    PreOrder(root);


    printf("\nThe Post Order Traversal Will be: \n");
    PostOrder(root);

    printf("\nThe In Order Traversal Will be: \n");
    InOrder(root);

    free_tree(root);
    return 0;
}