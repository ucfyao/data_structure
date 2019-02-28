#include <stdio.h>
#include <stdlib.h>

// 定义数据结构
typedef struct node
{
    int data;
    struct node * left;
    struct node * right;
} BSTree;

// 插入。左边的数据比右边的小。便于构建二叉排序树。
void insert(BSTree ** tree, int val){
    BSTree * temp = NULL;
    // 空树，进行初始化根节点
    if(!(*tree)){
        temp = (BSTree *) malloc(sizeof(BSTree));
        temp->left = temp->right = NULL;
        temp->data = val;
        *tree = temp;
        return;
    }
    // 判断节点是大于放在右树，还是小于放在左树
    if( val < (*tree)->data ){
        insert( &(*tree)->left, val);
    }else if( val > (*tree)->data ){
        insert( &(*tree)->right, val);
    }
}

// 删除节点
void del(BSTree *tree){    
    if(tree){
        del(tree->left);
        del(tree->right);
        free(tree);
    }
}

// 遍历树。前序。中左右
void printPre(BSTree *tree){
    if(tree){
        printf("%d\n",tree->data);
        printPre(tree->left);
        printPre(tree->right);
    }
}

// 遍历树。中序。左中右
void printIn(BSTree *tree){
    if(tree){
        printPre(tree->left);
        printf("%d\n",tree->data);
        printPre(tree->right);
    }
}
// 遍历树。后序。左右中
void printPost(BSTree *tree){
   if(tree){
        printPre(tree->left);
        printf("%d\n",tree->data);
        printPre(tree->right);
    }
}
// 最大深度
int maxDepth(BSTree *tree){
    if(tree == NULL){
        return 0;
    }

    int maxLeft = maxDepth(tree->left);
    int maxRight = maxDepth(tree->right);

    if(maxLeft > maxRight){
        return maxLeft+1;
    }else{
        return maxRight+1;  
    }

}

int main(){
    BSTree * root = NULL;
    BSTree * tmp = NULL;

    insert(&root,8);
    insert(&root,3);
    insert(&root,11);
    insert(&root,1);
    insert(&root,22);
    insert(&root,30);
    insert(&root,5);

    printf("Pre Display\n");
    printPre(root);

    printf("In Display\n");
    printIn(root);

    printf("Post Display\n");
    printPost(root);

    // printf("Del \n");
    // del(root);
    printf("Max depth %d \n",maxDepth(root));
    
}