#include <stdio.h>
#include <stdlib.h>

//�`�N�b���ŧitypedef����k�A�P�ҥ����t��

typedef struct _list_Node_ *listPointer; //�s�y�@�ӷs����ƫ��A �A  ���VlistNode����ƫ��A�٬�listPointer
typedef struct _list_Node_{
  int data;
  listPointer  link;

}listNode;//�s�@�@�ӷs����ƫ��A�A�٬�listNode�C����ƫ��A�]�tint �P listPointer
listPointer create2();
void printList(listPointer);
void insert(listPointer* ,listPointer ,int );

main(){

    listPointer first;
    first=create2();
    insert(&first,first,30);//������o��function�S������@�ΡH
    delete(&first,first,first->link); //�R��first->link�ҫ��V������
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
    }//�o�̪�*first �Pmain�̪�first���P�q   *first(in the insert function) ===  first(in the main function)
    //�e�ϥi�H�ܮe���z�ѳo�̪�����
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

