#include <stdio.h>
#define MAX_SIZE 100

struct cqueue{
    int arr[MAX_SIZE];
    int f;
    int b;
    int c;
};

void initialize(struct cqueue *q){
    q->f = -1;
    q->b = -1;
    q->c = 0;
}

void push(struct cqueue *q, int val){
    if((q->c == MAX_SIZE) || (((q->b)+1)%MAX_SIZE == q->f)){
        printf("Queue is full\n");
        return;
    }
    
    printf("init\n");
    q->arr[(++(q->b))%MAX_SIZE];
    (q->c)++;
}

void pop(struct cqueue *q){
    if(q->c==0){
        printf("Queue is empty\n");
        return;
    }
    
    printf("pop\n");
    (q->c)--;
    q->f = ((q->f)+1)%MAX_SIZE;
}

void front(struct cqueue *q){
    if(q->c==0){
        printf("No element in queue\n");
        return;
    }

    printf("front\n");
    printf("Front element is:%d\n",q->arr[q->f]);
}

void display(struct cqueue *q){   
    int s=q->f;
    while(s!= q->b){
	printf("s: %d ",s);
        printf("%d ",q->arr[s]);
        (++s)%MAX_SIZE;
    }
}

int main(){
    struct cqueue q1;
    
    initialize(&q1);
    push(&q1,15);
    push(&q1,20);
    push(&q1,25);
    push(&q1,30);
    push(&q1,35);
    pop(&q1);
    pop(&q1);
    front(&q1);
    display(&q1);
    display(&q1);
    return 0;
}
