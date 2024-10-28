#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

void traverse(struct Node *front)
{
    while (front != NULL)
    {
        printf("%d ", front->data);
        front = front->next;
    }
}

struct Node *enqueue(struct Node *f, struct Node **r, int val)
{
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    if (n == NULL)
    {
        printf("Queue is Full!\n");
        return f;
    }
    n->data = val;
    n->next = NULL;
    // if the queue is null
    if (f == NULL)
    {
        f = *r = n;
    }
    else
    {
        (*r)->next = n;
        *r = n;
    }
    return f;
}

struct Node *dequeue(struct Node *f, struct Node **r)
{
    if (f == NULL)
    {
        printf("Queue is Empty! No element present to dequeue\n");
        return f;
    }
    struct Node *temp = f;
    f = f->next;

    // if queue becomes empty
    if (f == NULL)
    {
        *r = NULL;
    }
    free(temp);
    return f;
}

int main()
{
    struct Node *f = NULL;
    struct Node *r = NULL;
    f = enqueue(f, &r, 44);
    f = enqueue(f, &r, 99);
    f = enqueue(f, &r, 65);

    printf("Elements of your Queue are: ");
    traverse(f);

    struct Node *temp;
    while (f != NULL)
    {
        temp = f;
        f = f->next;
        free(temp);
    }
    return 0;
}
