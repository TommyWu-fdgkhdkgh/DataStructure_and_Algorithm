#include <stdio.h>
#include <stdlib.h>

//注意在此宣告typedef的方法，與課本的差異

typedef struct _list_Node_ *listPointer; //製造一個新的資料型態 ，  指向listNode的資料型態稱為listPointer
typedef struct _list_Node_{
  int data;
  listPointer  link;

}listNode;//製作一個新的資料型態，稱為listNode。此資料型態包含int 與 listPointer
listPointer create2();
void printList(listPointer);
void insert(listPointer* ,listPointer ,int );

main(){

    listPointer first;
    first=create2();
    insert(&first,first,30);//為什麼這個function沒有任何作用？
    delete(&first,first,first->link); //刪除first->link所指向的元素
    printf("nothing!");
    printList(first);
}
listPointer create2(){
/* create a linked list with two nodes */
    listPointer first,second;

    first=(listNode*)malloc(sizeof(listNode));
    second=(listNode*)malloc(sizeof(listNode));
    second->link=NULL;
    second->data=20;
    first->data=10;
    first->link=second;


    return first;

}
void printList(listPointer first){
    printf("The list contains: ");
    for(;first;first=first->link)
        printf("%4d",first->data);
    printf("\n");
}
void insert(listPointer *first,listPointer x,int data){//insert a node with data
    listPointer temp;
    temp=(listNode*)malloc(sizeof(listNode));
    temp->data=data;
    printf("\ntest>>too");
    if(*first){
        temp->link=x->link;
        x->link=temp;
        printf("\ntest  in the first if");
    }
    else{
        temp->link=NULL;
        *first=temp;
        printf("\ntest>>else");
    }//這裡的*first 與main裡的first為同義   *first(in the insert function) ===  first(in the main function)
    //畫圖可以很容易理解這裡的概念
}
void delete(listPointer *first,listPointer trail,listPointer x){
    /* delete x from the list , trail is the preceding node and *first is the front of the list */
    if(trail){
        trail->link=x->link;
    }
    else{
        *first=(*first)->link;
    }
    free(x);
}

