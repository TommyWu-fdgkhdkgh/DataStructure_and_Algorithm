#include <stdio.h>
#include <stdlib.h>


#define MAX_STACK_SIZE 10
#define EXIT_FAILURE 1
typedef enum {
         true = 1 ==1 ,
         false =1 ==0
     }bool;

typedef struct {
        int key;
        /*other fields*/
    }element;


//MALLOC(stack,sizeof(*stack));
int capacity=1;
int top=-1;
element *stack;

bool IsEmpty(int);
bool IsFull(int);
void stackFull();
main(){
    stack=(element*)malloc(sizeof(*stack));//C��global�ܼƤ���Q�@��run-time�~�M�w���F��initialize

    element test;
    test.key=1;
    int i=0;
    for(i=0;i<1000;i++){
        push(test);
        printf("%d\n",top);
    }//���ɭԥi�Hcompile���\�A���ɭԷ|����
    //�M��{�b�����\�F???????????????
}
bool IsEmpty(int top){//detect if the stack is empty
    if(top<0){
        return true;
    }
    else{
        return false;
    }
}
bool IsFull(int top){//detect if the stack is full
    if(top>=capacity-1){
        return true;
    }
    else{
        return false;
    }
}
void stackFull(){
    stack=realloc(stack,2*capacity*sizeof(*stack));
    capacity*=2;
    printf("I haved come to stackFull\n");
}
void push(element item){
    /* add an item to the global stack */
    if(top>=capacity){
        stackFull();
    }
    stack[++top]=item;
}
void pop(){
    /* delete and return the pop element from the stack */
    if(top==-1){
        printf("the stack is Empty!");
    }
    return stack[top--];
}


/*  what do I learn?
    typedef �i�H�ŧi�b�~��
    basic stack
*/
