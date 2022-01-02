#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 8 /* maximum queue size */
//global variance
typedef struct{
    int key;
    /* other fields */
}element;
typedef enum {
         true = 1 ==1 ,
         false =1 ==0
}bool;


int capacity=MAX_QUEUE_SIZE;
//element queue[capacity];  Cglobal跑计ぃ砆run-time∕﹚狥﹁initialize
element* queue;
int rear=-1;
int front=-1;
//global variance//
//function
bool IsEmpty();
bool IsFull();
void queueFull();
void addq(element);
element deleteq();
//function//


main(){

/*//copy test
    int a[3];
    int b[3];

    a[0]=1;
    a[1]=2;
    a[2]=3;
    int i=0;
    for(i=0;i<3;i++){
        printf("%d\n",a[i]);
    }

    copy(a,a+3,b);

    for(i=0;i<3;i++){
        printf("%d\n",b[i]);
    }
//copy test//
//test >> there isn't any function called copy  */

    queue=(element*)malloc(8*sizeof(element));//initialize

    element test;
    test.key=1;

    addq(test);
    addq(test);
    addq(test);
    addq(test);
    addq(test);
    addq(test);
    addq(test);
    addq(test);
    addq(test);

    printf("front:%d\n",front);
    printf("rear:%d\n",rear);

}
bool IsEmpty(){
    if(front==rear){
        return true;
    }
    else{
        return false;
    }
}
bool IsFull(){
    if(rear==MAX_QUEUE_SIZE-1){
        return true;
    }
    else{
        return false;
    }
}
void queueFull(){//把σ揭セp122
    fprintf(stderr,"The queue is full!\n");


    element* newqueue;
    newqueue=(element*)malloc(2*sizeof(*queue));
    int start=(front+1)%capacity;
    if(start<2){
        /* no wrap around */
        copy(start,start+capacity-1,0,queue,newqueue);
    }
    else{
        /* queue wraps around */
        copy(start,capacity,0,queue,newqueue);
        copy(0,rear+1,0+capacity-start,queue,newqueue);
    }
    /* switch to newQueue */
    front=2*capacity-1;
    rear=capacity-2;
    capacity*=2;
    free(queue);
    queue=newqueue;
    //exit(EXIT_FAILURE);

}
void addq(element item){
    /* add an item to the queue */
    if((rear+1)>=capacity  &&  front==-1){//稱猭安璝常⊿Τdequeue尿じご穦犯
        rear=rear%capacity;
        queueFull();
        queue[rear]=item;
    }
    else{
        rear=(rear+1)%capacity;//make it circular
        if(rear==front){
            queueFull();/* double capacity */
        }
        queue[rear]=item;
    }
}
element deleteq(){
    /* remove element at the front of the queue */
    if(front==rear){
        printf("the queue is empty!!\n");/* return an error key */
        exit(EXIT_FAILURE);
    }
    front=(front+1)%MAX_QUEUE_SIZE;
    return queue[front];
}
void copy(int start, int end, int newstart,element* queue,element* newqueue){

    int i=0,j=0;
    for(i=0;i<end;i++){
        newqueue[j]=queue[i];
        j++;
    }
    //return newqueue;
}
