#include <stdio.h>
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

int top=-1;
element stack[MAX_STACK_SIZE];


bool IsEmpty(int);
bool IsFull(int);
void stackFull();

main(){


    element test;
    test.key=1;
    push(test);

    int i=0;
    for(i=0;i<10;i++){
        push(test);
    }
    pop();



    printf("%d\n",test.key);
    printf("%d",top);
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
    if(top>MAX_STACK_SIZE-1){
        return true;
    }
    else{
        return false;
    }
}
void stackFull(){
    fprintf(stderr,"Stack is full,cannot add element");
    exit(EXIT_FAILURE);
}
void push(element item){
    /* add an item to the global stack */
    if(top>=MAX_STACK_SIZE){
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
    typedef 可以宣告在外面

    basic stack

*/
