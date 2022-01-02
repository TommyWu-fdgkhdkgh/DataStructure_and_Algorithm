#include <stdio.h>
#include <stdlib.h>
/* 宣告 tree_node 是二元搜尋樹的節點 */
typedef struct node{
    struct node *leftChild;
    int data;
    struct node *rightChild;
}tree_node;

typedef enum {
         true = 1 ==1 ,
         false =1 ==0
}bool;



/* 宣告 tree_pointer 是指向節點的指標 */
typedef tree_node *tree_pointer;

void create_node(tree_pointer*,tree_pointer,bool,int);
void delete_node(tree_pointer*,tree_pointer,bool);
void inorder(tree_pointer);
void preorder(tree_pointer);
void postorder(tree_pointer);
tree_pointer search(tree_pointer,int);
tree_pointer search_recursive(tree_pointer root,int key);
tree_pointer insert_binary_search_tree(tree_pointer,int);


int main(){

    tree_pointer root;
    tree_pointer test_pointer;

    root=(tree_node*)malloc(sizeof(tree_node));
    root->data=20;
    //製造一個data為30的節點
    create_node(&root,root,true,10);
    create_node(&root,root,false,30);
    //創造了二層的完全二元樹，可以開始測試前中後序轉換
    test_pointer=root->leftChild;



    printf("%d",root->data);
    printf("%d",test_pointer->data);
    printf("\ntest inorder\n");
    inorder(root);
    printf("\ntest preorder\n");
    preorder(root);
    printf("\ntest postorder\n");
    postorder(root);



    //binary search tree
    test_pointer=search(root,20);
    printf("\ntest search\n");
    printf("%d",test_pointer->data);
    printf("\ntest insert\n");
    root=insert_binary_search_tree(root,50);
    inorder(root);

    return 0;
}
void create_node(tree_pointer *root,tree_pointer location,bool left_or_right,int data){
    //該增加節點的方式，只能在某節點NULL的枝的地方新增，無法insert
    //left_or_right   true->left    false->right
    tree_pointer temp;
    temp=(tree_node*)malloc(sizeof(tree_node));
    temp->data=data;

    if(*root){
        if(left_or_right){
            temp->leftChild=NULL;
            temp->rightChild=NULL;
            location->leftChild=temp;
        }
        else{
            temp->leftChild=NULL;
            temp->rightChild=NULL;
            location->rightChild=temp;
        }
    }
    else{//原本根指標沒有連接到任何節點
        temp->leftChild=NULL;
        temp->rightChild=NULL;
        *root=temp;
    }
}


void inorder(tree_pointer root){
    if(root){
        inorder(root->leftChild);
        printf("%d   ",root->data);
        inorder(root->rightChild);
    }
}
void preorder(tree_pointer root){
    if(root){
        printf("%d   ",root->data);
        preorder(root->leftChild);
        preorder(root->rightChild);
    }
}
void postorder(tree_pointer root){
    if(root){
        postorder(root->leftChild);
        postorder(root->rightChild);
        printf("%d   ",root->data);
    }
}
//binary search tree's operation
tree_pointer search(tree_pointer root,int key){
    tree_pointer current;
    current=root;
    while(current){
        if(key==current->data) return current;
        if(key<current->data){
            current=current->leftChild;
        }
        else{
            current=current->rightChild;
        }
    }
    return NULL;
}
tree_pointer search_recursive(tree_pointer root,int key){//搜尋的遞迴寫法
    if(!root) return NULL;
    if(key==root->data) return root;
    if(key>root->data){
        return search_recursive(root->rightChild,key);
    }
    else{
        return search_recursive(root->leftChild,key);
    }
}
tree_pointer insert_binary_search_tree(tree_pointer root,int key){
    tree_pointer ptr,current,previous;
    if(search(root,key)){
        printf("資料已經存在，無法再插入相同資料");
        return root;
    }
    ptr=(tree_pointer)malloc(sizeof(tree_node));
    ptr->data=key;
    ptr->leftChild=NULL;
    ptr->rightChild=NULL;
    if(!root) root=ptr;
    else{
        current=root;
        while(current){
            previous=current;
            if(ptr->data<current->data) current=current->leftChild;
            else current=current->rightChild;
        }
        if(ptr->data<previous->data) previous->leftChild=ptr;
        else previous->rightChild=ptr;
    }
    return root;
}







