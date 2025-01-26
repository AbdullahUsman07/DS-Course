#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};


// Function to find the in-order predecessor
struct Node* inOrderPredecessor(struct Node* root, struct Node* x)
{
    // Case no 1: If it has left subtree
    if(x->left!=NULL)
    {
        struct Node *current=x->left;
        while(current->right!=NULL)
        {
           current=current->right;
        }
        return current;
    }

    //Case no 2: if it has no left subtree
    struct Node *ancestor=root;
    struct Node *predecessor=NULL;
    
    // if the tree has only one root
    if(x==root)
    {
        return NULL;
    }
    while(ancestor!=NULL)
    {
        if(x->data > ancestor->data)
        {
            predecessor=ancestor;
            ancestor=ancestor->right;
        }
        else
        {
            ancestor=ancestor->left;
        }
    }

        return predecessor;
    
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

    printf("\nthe inOrder predecessor of %d is: ",r3->data);
    struct Node *result=inOrderPredecessor(root,r3);
    printf("%d ",result->data);
    free_tree(root);
   
    return 0;
}