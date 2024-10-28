#include<stdio.h>
#include<stdlib.h>

// In this program we will see how to find element in BST
// 
//         6
//        / \
//       4   7
//      / \   \
//     3   5   9

struct Node
{
    int data;
    struct Node *right;
    struct Node *left;
};

void free_tree(struct Node *root)
{
    if(root!=NULL)
    {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

struct Node *create_node(int data)
{
    struct Node *r;
    r=(struct Node*)malloc(sizeof(struct Node));
    r->data=data;
    r->left=NULL;
    r->right=NULL;

    return r;
}

void PreOrder(struct Node *root)
{
    if(root!=NULL)
    {
        printf("%d ",root->data);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

void InOrder(struct Node *root)
{
    if(root!=NULL)
    {
        InOrder(root->left);
        printf("%d ",root->data);
        InOrder(root->right);
    }
}

void PostOrder(struct Node *root)
{
    if(root!=NULL)
    {
        PostOrder(root->left);
        PostOrder(root->right);
        printf("%d ",root->data);
    }
}

// Recursive Search In BST
struct Node *search(struct Node *root,int key)
{
    if(root==NULL)
    {
        return NULL;
    }
    if(root->data==key)
    {
        return root;
    }
    else if(root->data<key)
    {
        return search(root->right,key);
    }
    else
    {
        return search(root->right,key);
    }
}

// iterative Search in BST
struct Node *search_iter(struct Node *root,int key)
{
    while(root!=NULL)
    {
        if(root->data==key)
        {
            return root;
        }
        else if(root->data<key)
        {
            root=root->right;
        }
        else
        {
            root=root->left;
        }
    }
    return NULL;
}


int main()
{
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

    printf("InOrder Traversal of BST is:\n");
    InOrder(root);

    struct Node *s=search_iter(root,9);
    if(s==NULL)
    {
        printf("\nNot Found!\n");
    }
    else
    {
        printf("\nFound: %d",s->data);
    }

    free_tree(root);
    return 0;
}