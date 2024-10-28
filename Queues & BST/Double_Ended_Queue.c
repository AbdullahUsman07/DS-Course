#include <stdio.h>
#include <stdlib.h>

// Two Types of DEqueue
// 1- Restricted Input DEqueue : insertion from front is not allowed
// 2- Restricted Output DEqueue: Deletion from Rear is not allowed

struct DEqueue
{
    int size;
    int f;
    int r;
    int *arr;
};

int isFull(struct DEqueue *q)
{
    return q->r == (q->size - 1);
}

int isEmpty(struct DEqueue *q)
{
    return q->f == q->r;
}


void traverse(struct DEqueue *q)
{
    if (isEmpty(q))
    {
        printf("Queue is Empty!\n");
        return;
    }
    for (int i = q->f + 1; i <= q->r; i++)
    {
        printf("%d ", q->arr[i]);
    }
    printf("\n");
}


struct DEqueue *EnqueueF(struct DEqueue *q, int data)
{
    if (q->f == -1)
    {
        printf("Cannot Insert at Front (Restricted Input DEqueue)\n");
        return q;
    }
    if (isFull(q))
    {
        printf("Queue is Full!\n");
        return q;
    }
    q->arr[q->f] = data;
    q->f--;
    return q;
}

struct DEqueue *EnqueueR(struct DEqueue *q, int data)
{
    if (isFull(q))
    {
        printf("Queue is Full!\n");
        return q;
    }
    q->r++;
    q->arr[q->r] = data;
    return q;
}

struct DEqueue *DequeueF(struct DEqueue *q)
{
    if (isEmpty(q))
    {
        printf("Queue is Empty!\n");
        return q;
    }
    q->f++;
    return q;
}

struct DEqueue *DequeueR(struct DEqueue *q)
{
    if (isEmpty(q))
    {
        printf("Queue is Empty!\n");
        return q;
    }
    if (q->r == -1)
    {
        printf("Cannot Delete from Rear (Restricted Output DEqueue)\n");
        return q;
    }
    q->r--;
    return q;
}

int main()
{
    struct DEqueue *q = (struct DEqueue *)malloc(sizeof(struct DEqueue));
    q->f = q->r = -1;

    printf("Input size of the Queue: ");
    scanf("%d", &q->size);
    q->arr = (int *)malloc(q->size * sizeof(int));

    int element;

    printf("Input Element That You want To insert at the Rear: ");
    scanf("%d", &element);
    q = EnqueueR(q, element);

    printf("Input Element That You want To insert at the Rear: ");
    scanf("%d", &element);
    q = EnqueueR(q, element);


    printf("The Elements of Your Queue Are:\n");
    traverse(q);

    free(q->arr);
    free(q);

    return 0;
}
