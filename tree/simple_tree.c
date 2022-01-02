#include <stdio.h>
#include <stdlib.h>
/* 宣告 tree_node 是二元搜尋樹的節點 */
typedef struct node{
    struct node *leftChild;
    char data;
    struct node *rightChild;
}tree_node;

typedef enum {
         true = 1 ==1 ,
         false =1 ==0
}bool;



/* 宣告 tree_pointer 是指向節點的指標 */
typedef tree_node *tree_pointer;

void create_node(tree_pointer*,tree_pointer,bool,char);
void delete_node(tree_pointer*,tree_pointer,bool);
void inorder(tree_pointer);
void preorder(tree_pointer);
void postorder(tree_pointer);

int main(){

    tree_pointer root;
    tree_pointer test_pointer;

    root=(tree_node*)malloc(sizeof(tree_node));
    root->data='a';
    //製造一個data為30的節點
    create_node(&root,root,true,'b');
    create_node(&root,root,false,'c');
    //創造了二層的完全二元樹，可以開始測試前中後序轉換
    test_pointer=root->leftChild;


    printf("%c",root->data);
    printf("%c",test_pointer->data);
    printf("\ntest inorder\n");
    inorder(root);
    printf("\ntest preorder\n");
    preorder(root);
    printf("\ntest postorder\n");
    postorder(root);

    delete_node(&root,root,true);
    if(!root->leftChild){
        printf("\ndelete success");
    }
    else{
        printf("delete fail");
    }


    return 0;
}
void create_node(tree_pointer *root,tree_pointer location,bool left_or_right,char data){
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
void delete_node(tree_pointer *root,tree_pointer location , bool left_or_right){
    //該刪除只能把某個節點徹底消除，一併消除該節點的子節點
    if(root){
        if(left_or_right){
            free(location->leftChild);
            location->leftChild=NULL;
        }
        else{
            free(location->rightChild);
            location->rightChild=NULL;
        }
    }
    else{
        printf("It's a empty tree!Can't delete any node.");
    }
}
void inorder(tree_pointer root){
    if(root){
        inorder(root->leftChild);
        printf("%c   ",root->data);
        inorder(root->rightChild);
    }
}
void preorder(tree_pointer root){
    if(root){
        printf("%c   ",root->data);
        preorder(root->leftChild);
        preorder(root->rightChild);
    }
}
void postorder(tree_pointer root){
    if(root){
        postorder(root->leftChild);
        postorder(root->rightChild);
        printf("%c   ",root->data);
    }
}


//缺新增節點，刪除節點
/* implement simple tree and five kinds of traversal>> inorder , preorder , postorder, iterative inorder , level-order  */
