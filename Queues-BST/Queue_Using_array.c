#include<stdio.h>
#include<stdlib.h>

struct Queue{
    int size;
    int f; //f for front;
    int b; //it will indicate the last element
    int *arr;
};

void traverse(struct Queue *q)
{
    for(int i=q->f+1;i<=q->b;i++)
    {
        printf("%d ",q->arr[i]);
    }
}

int isEmpty(struct Queue *q)
{
    // Queue is Empty when front and back are at the same position
    return q->f==q->b;
}

int isFull(struct Queue *q)
{
    // Queue is Full when is present at the last index
    return q->b==q->size-1;
}

// Enqueue is used to insert element in the Queue
void Enqueue(struct Queue *q,int data)
{
    if(!isFull(q))
    {
        q->b++;
        q->arr[q->b]=data;
        return;
    }
    printf("Queue Overflow!\n");
}

// Dequeue is used to remove elements from the Queue
// Unlike Stack Queue is First in First out (FIFO)
int Dequeue(struct Queue *q)
{
    if(isEmpty(q))
    {
        return -1;
    }
    q->f++;
    return q->arr[q->f];
}


int main()
{
    struct Queue *q=(struct Queue*)malloc(sizeof(struct Queue));
    // initialize the First and Back Index
    q->f = q->b = -1;
    printf("Input the Size of Your Queue: ");
    scanf("%d",&q->size);

    q->arr=(int *)malloc(q->size * sizeof(int));
    int val;
    printf("Input Element that you want to insert into your Queue: ");
    scanf("%d",&val);
    Enqueue(q,val);

    printf("Input Element that you want to insert into your Queue: ");
    scanf("%d",&val);
    Enqueue(q,val);

    printf("Input Element that you want to insert into your Queue: ");
    scanf("%d",&val);
    Enqueue(q,val);

    printf("The Elements of Your Queue Are: \n");
    traverse(q);
    free(q->arr);
    free(q);
    return 0;
}