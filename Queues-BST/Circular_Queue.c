#include<stdio.h>
#include<stdlib.h>

// Circular Queue is Just Like Linear Queue with Circular Increment
// Linear Increment is: n=n+1;
// Circular Increment is : n=(n+1)%size 
// In circular increment when the counter reaches at the last index it will jump to the start

struct CircularQueue{
    int size;
    int f; // f for front
    int r; // r for rare
    int *arr;
};

int isEmpty(struct CircularQueue *q)
{
    return q->f==q->r;
}

// The Queue is Full if we circular increment the rare and it becomes equal to the front
int isFull(struct CircularQueue *q)
{
    return (q->r+1)%q->size==q->f;
}

void traverse(struct CircularQueue *q)
{
    if(isEmpty(q))
    {
        printf("Your Queue is Empty!\n");
        return;
    }
    int i=(q->f+1)%q->size;
    do
    {
        printf("%d ",q->arr[i]);
        i=(i+1)%q->size;
    } while (i!=(q->r+1)%q->size);
    
}

void Enqueue(struct CircularQueue *q,int data)
{
    if(isFull(q))
    {
        printf("Queue is Full!\n");
        return;
    }
    q->r=(q->r+1)%q->size;
    q->arr[q->r]=data;
}

int Dequeue(struct CircularQueue *q)
{
    if(isEmpty(q))
    {
        printf("Queue is Empty!\n");
        return -1;
    }
    q->f=(q->f+1)%q->size;
    return q->arr[q->f];
}

int main()
{
    struct CircularQueue *q=(struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    
    printf("Input Size of your Queue: ");
    scanf("%d",&q->size);
    q->f=q->r=0;
    q->arr=(int*)malloc(q->size*sizeof(int));
    
    // In circular queue the front and rare start from the 0 index so we could only use size-1 spaces
    int element;
    for(int i=0;i<q->size-1;i++)
    {
        printf("Input Element that you want to Enqueue: ");
        scanf("%d",&element);
        Enqueue(q,element);
    }

    printf("The elements of your queue are: \n");
    traverse(q);

    free(q->arr);
    free(q);
    return 0;
}